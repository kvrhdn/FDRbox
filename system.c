#include "system.h"

#include <xc.h>

#include "led.h"
#include "usb_device.h"
#include "usb_midi.h"

// CONFIG1
#pragma config FOSC = INTOSC	// Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF		// Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF		// Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON		// MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF			// Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON		// Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF	// Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF		// Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF		// Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF		// Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Selection Bit (NO CPU system divide)
#pragma config USBLSCLK = 48MHz	// USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x		// PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = ENABLED	// PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = ON		// Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO		// Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF		// Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF		// Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

void system_initialize()
{
	// Oscillator settings
	OSCCON = 0xFC;	/* Oscillator control register
					 * 7	SPLLEN = x
					 * 6	SPLLMULT = 1 (3x multiplier)
					 * 5:2	IRCF = 1111 (16 MHz INTOSC)
					 * 1:0	SCS = 00 (clock defined by configuration words)		*/
	ACTCON = 0x90;	/* Active Clock Tuning control register
					 * 7	ACTEN = 1 (ACT enabled)
					 * 6	ACTUD = 0 (updates enabled)
					 * 5	x
					 * 4	ACTSRC = 1 (use Fll-speed USB events)
					 * 3	ACTLOCK (read-only)
					 * 2	x
					 * 1	ACTORS (read-only)
					 * 0	x													*/

	// Enable weak pull-ups
	OPTION_REGbits.nWPUEN = 0;
	// Disable analog inputs
#ifdef _16F1455
	ANSELAbits.ANSA4 = 0;
	ANSELC = 0x00;
#endif

	// LED
	led_initialize();

	// USB - automatically calls MIDI_Initialize when ready
	USBDeviceInit();
	USBDeviceAttach();

	// Block until USB is fully configured
	while ( USBGetDeviceState() < CONFIGURED_STATE )
		led_tasks();

	led_set_idle();
}

void system_tasks()
{
	midi_tasks();
	led_tasks();
}

void interrupt SYS_InterruptHigh(void)
{
	USBDeviceTasks();
}
