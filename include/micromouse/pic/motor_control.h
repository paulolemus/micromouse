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


void update_mc_state();

void wait_mc();

/**
 * @brief Use this function to set the operation that the motor controller will
 *        execute.
 * @param motor_control_func pointer to the non-blocking execution function.
 */
void set_motor_control_function(void (*motor_control_func)(void));


///
/// Motor Controller Functions
///

/**
 * The motors will hold their current positions.
 */
void init_position_mc();
void position_mc();

/**
 * The mouse will drive in a straight line.
 */
void init_straight_mc();
void straight_mc();


/**
 * The mouse will track against a wall if there is one to track against.
 */
void init_track_mc();
void track_mc();

void init_left_mc();
void left_mc();

void init_right_mc();
void right_mc();

void init_around_mc();
void around_mc();


#ifdef	__cplusplus
}
#endif

#endif	// MICROMOUSE_PIC_MOTOR_CONTROL_H_

