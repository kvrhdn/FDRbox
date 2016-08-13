#include <xc.h>
#include "led.h"

#define LED	LATCbits.LATC4

/* Use Timer2, the built-in comparator is useful for keeping the timer running 
 * continuously. Timer2 will raise a flag every 1 mSec and reset itself. The
 * application just has to poll this flag fast enough.
 * 
 * Disadvantage: can't use Timer2 for PWM (except when the period is 1 mSec?)
 */

static uint16_t led_count = 0;		// 1 count = 1 mSec
static uint16_t led_high = 100;
static uint16_t led_period = 200;

static uint8_t led_blink_count = 0;
static uint8_t led_blink_enable = 0;

void led_initialize()
{
	// LED pin
	TRISCbits.TRISC4 = 0;
	LED = 1;

	// Initialize Timer2
	/* Input clock is Fosc/4 = 12 MHz --> 83,33... nSec --> 12.000 clk = 1 mSec
	 * - post-scaler = 1:3
	 * - pre-scaler = 1:16
	 * - reset at 250
	 */
	T2CON = 0x16;	/* Timer2 control register
					 * 7	x
					 * 6:3	T2OUTPS = 0010 (1:3 post-scaler)
					 * 2	TMR2ON = 1
					 * 1:0	T2CKPS = 10 (1:16 pre-scaler)						*/
	PR2 = 250;		// TMR2 resets when it reaches this value
}

void led_set_rate( uint16_t high_time, uint16_t period )
{
	led_high = high_time;
	led_period = period;
}

void led_blink()
{
	led_blink_enable = 1;
}

void led_tasks()
{
	if ( PIR1bits.TMR2IF ) {
		PIR1bits.TMR2IF = 0;

		if ( led_blink_enable ) {	// blinking has priority
			LED = ( led_blink_count < 50 );

			if ( ++led_blink_count >= 100 ) {
				led_blink_count = 0;
				led_blink_enable = 0;
			}
		} else {
			LED = ( led_count < led_high );
		}

		if ( ++led_count >= led_period )
			led_count = 0;
	}
}
