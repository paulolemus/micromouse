/**
 * File:
 *     oscillator.h
 *
 * Description:
 *     Hardware level functions for interacting with the oscillator.
 *
 * Notes:
 *     Before any functions are used, the init function must be called.
 *
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_PIC_COMPONENTS_OSCILLATOR_H_
#define MICROMOUSE_PIC_COMPONENTS_OSCILLATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the oscillator in hardware.
 *        Must be called before anything that requires a configured oscillator.
 */
void init_oscillator();


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_PIC_COMPONENTS_OSCILLATOR_H_
