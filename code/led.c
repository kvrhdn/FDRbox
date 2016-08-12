#include <xc.h>
#include "led.h"

#define LED	LATCbits.LATC4

#define TMR0_1_MS	0x5E	// = 1,00266... mSec

static uint16_t led_count = 0;
static uint16_t led_high = 100;
static uint16_t led_period = 200;

static uint8_t led_blink_count = 0;
static uint8_t led_blink_amount = 0;

void led_initialize()
{
	// LED pin
	TRISCbits.TRISC4 = 0;
	LED = 1;

	// Timer 0
	OPTION_REGbits.TMR0CS = 0;	// use as timer: source is Fosc/4
	OPTION_REGbits.PSA = 0;		// enable prescaler
	OPTION_REGbits.PS = 0b110;	// set prescaler to 128:1

	TMR0 = 0x00 - TMR0_1_MS;
}

void led_set_rate( uint16_t high_time, uint16_t period )
{
	led_high = high_time;
	led_period = period;
}

void led_blink()
{
	++led_blink_amount;
}

void led_tasks()
{
	if ( INTCONbits.TMR0IF == 1 ) {	// flag is set when TMR0 overflows, every 1 mSec
		INTCONbits.TMR0IF = 0;

		TMR0 -= TMR0_1_MS;	// take possible jitter into account

		if ( led_blink_amount ) {	// blinking has priority
			LED = ( led_blink_count < 50 );

			if ( ++led_blink_count >= 100 ) {
				led_blink_count = 0;
				led_blink_amount--;
			}
		} else {
			LED = ( led_count < led_high );
		}

		if ( ++led_count >= led_period )
			led_count = 0;
	}
}
