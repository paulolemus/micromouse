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


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_PIC_COMPONENTS_LED_H_
