/**
 * File:
 *     motor.h
 *
 * Description:
 *     Hardware level functions for interacting with the motors..
 *
 * Notes:
 *     Before any functions are used, the init function must be called.
 *     The mouse has two DC motors.
 *
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_PIC_COMPONENTS_MOTOR_H_
#define MICROMOUSE_PIC_COMPONENTS_MOTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the motors in hardware.
 *        Must be callled before any other functions related to the motors are called.
 */
void init_motor();


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_PIC_COMPONENTS_MOTOR_H_
