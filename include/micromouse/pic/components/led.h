/**
 * File:
 *     led.h
 *
 * Description:
 *     Hardware level functions for interacting with the leds.
 *
 * Notes:
 *     Before any functions are used, the init function must be called.
 *     The mouse has one RGB LED, and two yellow LEDs.
 *
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_PIC_COMPONENTS_LED_H_
#define MICROMOUSE_PIC_COMPONENTS_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the LED ports in hardware. 
 *        Must be called before using LEDs.
 */
void init_led();


// LED RGB PORTS
#define RGB_R LATAbits.LATA9
#define RGB_G LATCbits.LATC3
#define RGB_B LATCbits.LATC4

// LED SIGNAL PORTS
#define LED_L LATAbits.LATA4
#define LED_R LATCbits.LATC5

// LED interaction macros
#define LED_ON(led_lat)     led_lat = 1
#define LED_OFF(led_lat)    led_lat = 0
#define LED_TOGGLE(led_lat) led_lat = ~led_lat


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_PIC_COMPONENTS_LED_H_
