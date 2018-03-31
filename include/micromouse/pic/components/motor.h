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
    
    
///
/// Motor macros
///

// Motor direction pins
#define L_MTR_DIR LATBbits.LATB13
#define R_MTR_DIR LATBbits.LATB15
    
// Motor direction enums TODO
#define L_MTR_FWD 0
#define L_MTR_REV 1
#define R_MTR_FWD 1
#define R_MTR_REV 0

/**
 * @brief Initialize the motors in hardware.
 *        Must be callled before any other functions related to the motors are called.
 */
void init_motor();


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_PIC_COMPONENTS_MOTOR_H_
