/**
 * File:
 *     motor_control.h
 *
 * Description:
 *     The motor control module provides an API that that allows for simple
 *     motor maneuvers.
 *     For example, there are modules for turning, driving straight, tracking.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */    

#ifndef MICROMOUSE_PIC_MOTOR_CONTROL_H_
#define MICROMOUSE_PIC_MOTOR_CONTROL_H_

#ifdef	__cplusplus
extern "C" {
#endif


/**
 * Set the initial state of the motor control module.
 * This must be called before any other functions from this module are used.
 * The MC module depends on:
 *     ADC, QEI.
 * Ensure those are enabled prior to enabling motor_control.
 */
void init_motor_control();


/**
 * Enable the motor control module.
 */
void enable_motor_control();


/**
 * Disable the motor control module.
 */
void disable_motor_control();


#ifdef	__cplusplus
}
#endif

#endif	// MICROMOUSE_PIC_MOTOR_CONTROL_H_

