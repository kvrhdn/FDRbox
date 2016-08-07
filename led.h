#ifndef LED_H
#define	LED_H

#include <stdint.h>

/**
 * Has to be called before calling any other function to configure the LED.
 */
void led_initialize( void );

/**
 * Change the rate at which the LED blinks. The LED will blink every period
 * milliseconds for high_time milliseconds.
 */
void led_set_rate( uint16_t high_time, uint16_t period );

/**
 * Macro to set rate to idle blinking.
 */
#define led_set_idle()	led_set_rate( 200, 5000 );

/**
 * Blink once. If the LED is already blinking, blink more afterwards.
 */
void led_blink( void );

/**
 * Should be called regularly to update the LED state.
 */
void led_tasks( void );

#endif // LED_H
