#include <xc.h>

#include "led.h"
#include "system.h"
#include "usb_midi.h"

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
 * Caution has to be taken to not restart the ADC directly after switching the 
 * channel.
 *																				// TODO test this
 * Since the ADC has a bit of jitter in between measurements (which causes it to
 * 'fluctuate' between two values), a 'filter' is applied:
 * - a buffer is kept with the last BUFFER_DEPTH values
 * - if the measured is already present in the buffer (= has been recently
 *   transmitted), the value is ignored.
 * Tests showed a buffer of 3 works very well.
 * Disadvantage: when changing direction, there is a jump of 3 values.
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

/* Function wraps the actual hardware channels. If this function is called
 * FDR_AMT times every fader has been chosen once.
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

#define BUFFER_DEPTH	3

typedef struct {
	uint8_t result[ BUFFER_DEPTH ];	// circular buffer
	uint8_t last_updated;			// index of result[]
} ResultBuffer;

static ResultBuffer fdr_buffer[ FDR_AMT ];

/***** MIDI *******************************************************************/

static MidiPacket packet = { CONTROL_CHANGE, 0, 0 };

/***** main *******************************************************************/

void main( void )
{
	system_initialize();

	// indicate that we are updating
	led_set_rate( 500, 1000 );													// TODO is this necessary? this will be rather quick

	// initialize mutiplexer
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

	ADCON0bits.ADGO = 1;		// start first conversion

	// update entire fdr_buffer first
	for ( uint8_t i = 0; i < FDR_AMT; ++i ) {

		while ( ADCON0bits.ADGO )	// block until conversion is done
			system_tasks();

		uint8_t measurement = ( ADRESH >> 1 );
		uint8_t fdr_measurement = mux_channel;
		mux_switch_next();

		for ( uint8_t j = 0; j < BUFFER_DEPTH; ++j )
			fdr_buffer[ fdr_measurement ].result[ j ] = measurement;
		fdr_buffer[ fdr_measurement ].last_updated = 0;

		ADCON0bits.ADGO = 1;
	}

	led_set_idle();

/***** main loop **************************************************************/

	for (;;) {
		system_tasks();

		if ( ! ADCON0bits.ADGO ) {		// conversion is done
			uint8_t measurement = ( ADRESH >> 1 );
			uint8_t fdr_measurement = mux_channel;

			mux_switch_next();

			// scan previous samples for duplicates (= filter)
			uint8_t i = 0;
			while ( i < BUFFER_DEPTH ) {
				if ( fdr_buffer[ fdr_measurement ].result[ i ] == measurement )
					break;
				++i;
			}

			if ( i == BUFFER_DEPTH ) {	// input is not yet in ResultBuffer
				// add to buffer
				fdr_buffer[ fdr_measurement ].result[ fdr_buffer[ fdr_measurement ].last_updated ] = measurement;
				fdr_buffer[ fdr_measurement ].last_updated = ( fdr_buffer[ fdr_measurement ].last_updated + 1 ) % BUFFER_DEPTH;

				// send MIDI update
				packet.key = fdr_measurement;
				packet.value = measurement;
				midi_send( &packet, 1 );
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
