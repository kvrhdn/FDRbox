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
 * already caused by the regular, no additional delay is implemented.
 *																				// TODO test this
 * Since the ADC has a bit of jitter in between measurements (which causes it to
 * 'fluctuate' between two values), a 'filter' is applied:
 * - a buffer is kept with the last couple of values
 * - if the measured is already present in the buffer (recently transmitted),
 *   the value is not transmitted.
 * Experimentation found a buffer of 3 works very well.
 * 
 * Disadvantage: when changing direction, there is a jump of 3 values.
 */

#ifndef _16F1455
#error Switch configuration to PIC16F1455 pls
#endif

/***** I/O *****/

#define FDR_AMT	8

#define MUX_CH2	LATCbits.LATC3
#define MUX_CH1	LATCbits.LATC5
#define MUX_CH0	LATAbits.LATA4

#define AN_CH	6	// AN6 = RC2

/***** MUX *****/

static uint8_t mux_channel = 0;

																				// TODO some useful macro's to switch channel?
																				// how are we gonna do this grey code madness?

/***** DATA *****/

#define BUFFER_DEPTH	3

typedef struct {
	uint8_t result[ BUFFER_DEPTH ];
	uint8_t last_updated;	// index - circular buffer
} ResultBuffer;

static ResultBuffer fdr_buffer[ FDR_AMT ];

/***** MIDI *****/

static MidiPacket packet = { CONTROL_CHANGE, 0, 0 };

void main( void )
{
	system_initialize();

	// indicate that we are updating
	led_set_rate( 500, 1000 );													// TODO is this necessary? this will be rather quick

	// initialize control of MUX
	TRISCbits.TRISC3 = 0;
	TRISCbits.TRISC5 = 0;
	TRISAbits.TRISA4 = 0;
	MUX_CH0 = 0;																// TODO
	MUX_CH1 = 0;
	MUX_CH2 = 0;
	mux_channel = 0;

	// initialize ADC
	TRISCbits.TRISC2 = 1;
	ANSELCbits.ANSC2 = 1;

	ADCON0bits.CHS = AN_CH;	// ADC channel
	ADCON1 = 0x60;	/* A/D control register 1
					 * 7	ADFM = 0 (left-justified, only need 7 bit)
					 * 6:4	ADCS = 110 (Fosc / 64)
					 * 3:2	x
					 * 1:0	PREF = 00 (Vref+ is connected to VDD)				*/
//	ADCON2 = 0x00;	/* A/D control register 2
//					 * 6:4	TRIGSEL = 000 (no auto-conversion)					*/
	ADCON0bits.ADON = 1;	// enable ADC

	// update entire fdr_buffer first
	for ( uint8_t i = 0; i < FDR_AMT; ++i ) {
		ADCON0bits.ADGO = 1;		// start conversion

		while ( ADCON0bits.ADGO )	// block until done
			system_tasks();

		// switch channel
																				// TODO write wrapper MACRO / function?

		for ( uint8_t j = 0; j < BUFFER_DEPTH; ++j )
			fdr_buffer[ i ].result[ j ] = ( ADRESH >> 1 );
		fdr_buffer[ i ].last_updated = 0;
	}

	led_set_idle();
	ADCON0bits.ADGO = 1;

	for (;;) {
		system_tasks();

		if ( ! ADCON0bits.ADGO ) {	// conversion is done
			ResultBuffer * fdr = &fdr_buffer[ mux_channel ];
			uint8_t input = ( ADRESH >> 1 );

			// switch channel
																				// TODO this has to happen in the real thing

			// scan previous samples for duplicates (= filter)
			uint8_t i = 0;
			while ( i < BUFFER_DEPTH ) {
				if ( fdr->result[ i ] == input )
					break;
				++i;
			}

			if ( i == BUFFER_DEPTH ) {	// input is not yet in ResultBuffer
				// add to buffer
				fdr->result[ fdr->last_updated ] = input;
				fdr->last_updated = ( fdr->last_updated + 1 ) % BUFFER_DEPTH;

				// send MIDI update
				packet.key = mux_channel;
				packet.value = input;
				midi_send( &packet, 1 );
			}

			mux_channel = ( mux_channel + 1 ) % FDR_AMT;						// TODO

			// restart conversion
			ADCON0bits.ADGO = 1;
		}
	}
}

void midi_receive( MidiPacket packet[], uint8_t num )
{
	// ignore all incoming MIDI
}
