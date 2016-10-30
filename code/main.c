#include <xc.h>

#include "led.h"
#include "system.h"
#include "usb_midi.h"

// TODO get 'official' VID+PID, currently using Microchip's VID. see usb_config.h

/**
 * Overview of pins capabilities (only most common used peripherals).
 * Project works with PIC16F1454 and PIC16F1455. PIC16F1459 is not tested.
 * 
 * RA0/RA1 are used for USB.
 * RA3 is used for MCLR with internal pull-up enabled.
 * RC4 is wired to the LED. Timer2 is used by the LED.
 * 
 * General purpose I/O:
 * 
 *			IOC		WPU		ICSP	SPI		I2C		PWM		ADC (1455 only)
 * RA4		x		x				SDOalt					AN3
 * RA5		x		x								PWM2alt
 * RC0						DAT		SCK		SCL				AN4
 * RC1		INT				CLK		SDI		SDA				AN5
 * RC2								SDO						AN6
 * RC3								SS				PWM2	AN7
 * RC5												PWM1
 * 
 * All weak pull-ups are enabled by default and can be independently configured
 * with WPUA.
 */

/* FDRbox
 * 
 * 8 faders are connected to an analog 8:1 MUX.
 * Analog in is connected to RC2 (AN6).
 * Channels of MUX are connected to RC3 : RC5 : RA4 (MSB -> LSB)
 * 
 * The MUX needs a certain time to switch channel, this shouldn't take longer
 * than 1 µSec (12 instructions at Fosc = 48 MHz). We assume this delay is
 * already caused by the regular code, no additional delay is implemented.
 * Caution has to be taken to not start conversion directly after switching the 
 * channel.
 * Since the ADC has some noise on the measurements, some filtering is applied.
 */

#ifndef _16F1455
#error Switch configuration to PIC16F1455 pls
#endif

/***** mux ********************************************************************/

/* The faders are connected according to grey code, so you should only need to
 * change 1 pin when scanning the channels sequentially.
 * Guess what, it only complicates stuff and mistakes are made. Not worth it.
 * 
 * Connections according to the schematic:
 * 
 * FDR_0	0	000
 * FDR_1	1	001
 * FDR_2	3	011
 * FDR_3	2	010
 * FDR_4	7	111		// FDR_4 and FDR_5 should have been switched for proper grey code
 * FDR_5	6	110
 * FDR_6	4	100		// FDR_6 and FDR_7 should have been switched for proper grey code
 * FDR_7	5	101
 * 
 * Instead of doing the grey code wiring in hardware, it could also have been
 * implemented in software by scanning the channels in a specific sequence.
 */

#define FDR_AMT	8

#define MUX_CH2	LATCbits.LATC3	// MSB
#define MUX_CH1	LATCbits.LATC5
#define MUX_CH0	LATAbits.LATA4	// LSB

static uint8_t mux_channel = 0;	// the fader currently connected

inline static
void mux_initialize()
{
	TRISCbits.TRISC3 = 0;
	TRISCbits.TRISC5 = 0;
	TRISAbits.TRISA4 = 0;

	mux_channel = 0;
	MUX_CH2 = 0;
	MUX_CH1 = 0;
	MUX_CH0 = 0;
}

/* Switch to the next channel. If this function is called FDR_AMT times every
 * fader has been chosen once.
 * Changes the variable mux_channel as well.
 */
inline static
void mux_switch_next()
{
	switch ( mux_channel ) {
		case 0:				// 000
			mux_channel = 1;// 001
//			MUX_CH2 = 0;
//			MUX_CH1 = 0;
			MUX_CH0 = 1;
			break;
		case 1:				// 001
			mux_channel = 2;// 011
//			MUX_CH2 = 0;
			MUX_CH1 = 1;
//			MUX_CH0 = 1;
			break;
		case 2:				// 011
			mux_channel = 3;// 010
//			MUX_CH2 = 0;
//			MUX_CH1 = 1;
			MUX_CH0 = 0;
			break;
		case 3:				// 010
			mux_channel = 5;// 110
			MUX_CH2 = 1;
//			MUX_CH1 = 1;
//			MUX_CH0 = 0;
			break;
		case 5:				// 110
			mux_channel = 4;// 111
//			MUX_CH2 = 1;
//			MUX_CH1 = 1;
			MUX_CH0 = 1;
			break;
		case 4:				// 111
			mux_channel = 7;// 101
//			MUX_CH2 = 1;
			MUX_CH1 = 0;
//			MUX_CH0 = 1;
			break;
		case 7:				// 101
			mux_channel = 6;// 100
//			MUX_CH2 = 1;
//			MUX_CH1 = 0;
			MUX_CH0 = 0;
			break;
		case 6:				// 100
			mux_channel = 0;// 000
			MUX_CH2 = 0;
//			MUX_CH1 = 0;
//			MUX_CH0 = 0;
			break;
	}
}

/***** data *******************************************************************/

/* Since measurements sometimes fluctuate between two values, due to noise in
 * the circuit or ADC, filtering is applied on the measurements.
 * 
 * There are two systems:
 * 
 *	-	every channel is sampled BUFFER_AVG times and the average is taken of
 *		these samples. This stabilizes measurements.
 *		If BUFFER_AVG is too high it will slow down updates.
 * 
 *	-	a buffer is kept of the last BUFFER_DEPTH transmitted values. If a new
 *		measurement is already present in the buffer, it is ignored since it was
 *		recently transmitted. This suppresses fluctuating between two values
 *		very efficiently.
 *		If BUFFER_DEPTH is too high there is a large jump in values when
 *		changing directions.
 */

#define BUFFER_AVG		2	// the amount of samples to average over, use a power of 2
#define BUFFER_DEPTH	2	// the amount of last sent values to buffer

static uint8_t avg_sum = 0;	// sum of averages, use uint16_t if BUFFER_AVG > 2
static uint8_t avg_amt = 0;	// the amount of averages taken so far

typedef struct {
	uint8_t result[ BUFFER_DEPTH ];	// circular buffer with last transmitted values
	uint8_t last_updated;			// index in result[]
} ResultBuffer;

static ResultBuffer fdr_buffer[ FDR_AMT ];

/***** main *******************************************************************/

void main( void )
{
	system_initialize();

	// initialize multiplexer
	mux_initialize();

	// initialize ADC
	TRISCbits.TRISC2 = 1;
	ANSELCbits.ANSC2 = 1;

	ADCON0bits.CHS = 6;	// RC2 = AN6
	ADCON1 = 0x60;	/* A/D control register 1
					 * 7	ADFM = 0 (left-justified, only need 7 bit)
					 * 6:4	ADCS = 110 (Fosc / 64)
					 * 3:2	x
					 * 1:0	PREF = 00 (Vref+ is connected to VDD)				*/
//	ADCON2 = 0x00;	/* A/D control register 2
//					 * 6:4	TRIGSEL = 000 (no auto-conversion)					*/

	ADCON0bits.ADON = 1;	// enable ADC

	ADCON0bits.ADGO = 1;	// start first conversion

	// update entire fdr_buffer first
	for ( uint8_t i = 0; i < FDR_AMT; ++i ) {

		while ( ADCON0bits.ADGO );	// block until conversion is done

		uint8_t measurement = ( ADRESH >> 1 );
		uint8_t fdr_measurement = mux_channel;

		mux_switch_next();

		for ( uint8_t j = 0; j < BUFFER_DEPTH; ++j )
			fdr_buffer[ fdr_measurement ].result[ j ] = measurement;
		fdr_buffer[ fdr_measurement ].last_updated = 0;

		ADCON0bits.ADGO = 1;
	}

/***** main loop **************************************************************/

	for (;;) {
		system_tasks();

		if ( ! ADCON0bits.ADGO ) {	// conversion is done

			avg_sum += ( ADRESH >> 1 );
			avg_amt += 1;

			if ( avg_amt == BUFFER_AVG ) {	// avg_sum has BUFFER_AVG samples

				// switch to next channel already - give MUX time to settle
				uint8_t fdr_measurement = mux_channel;
				mux_switch_next();

				// take average
				avg_sum /= BUFFER_AVG;

				// scan previous samples for recently transmitted values
				uint8_t i = 0;
				while ( i < BUFFER_DEPTH ) {
					if ( fdr_buffer[ fdr_measurement ].result[ i ] == avg_sum )
						break;
					++i;
				}

				if ( i == BUFFER_DEPTH ) {	// input is not yet in ResultBuffer
					// add to circular buffer
					fdr_buffer[ fdr_measurement ].result[ fdr_buffer[ fdr_measurement ].last_updated ] = avg_sum;
					fdr_buffer[ fdr_measurement ].last_updated = ( fdr_buffer[ fdr_measurement ].last_updated + 1 ) % BUFFER_DEPTH;

					// send MIDI update
					MidiPacket packet = { CONTROL_CHANGE, 0, 0 };
					packet.key = fdr_measurement;
					packet.value = avg_sum;

					midi_send( &packet, 1 );	// no error handling, packet is dropped if transmission failed
				}

				avg_sum = 0;
				avg_amt = 0;
			}

			// restart conversion
			ADCON0bits.ADGO = 1;
		}
	}
}

void midi_receive( MidiPacket packet[], uint8_t num )
{
	// ignore all incoming MIDI
}
