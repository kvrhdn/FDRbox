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

void main( void )
{
	system_initialize();

	// initialize your own I/O and peripherals

	for (;;) {																	// TODO test timing main loop
		system_tasks();															// TODO what if USB gets detached in the meantime? monitor state?

		// scan your inputs, update outputs
	}
}

void midi_receive( MidiPacket packet[], uint8_t num )
{
	// process incoming MIDI packets

	// for now, just mirror all data
	midi_send( packet, num );
}
