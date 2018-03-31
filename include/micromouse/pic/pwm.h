/**
 * File:
 *     pwm.h
 *
 * Description:
 *     The PWM module acts as an interface through which we modify PWM signals.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */    

#ifndef MICROMOUSE_PIC_PWM_H_
#define MICROMOUSE_PIC_PWM_H_

#ifdef	__cplusplus
extern "C" {
#endif
    
///
/// PWM macros
///

// Motor duty cycle / period registers
#define L_MTR_PER P1DC2
#define R_MTR_PER P1DC1

/// Duty upper and lower bounds
#define L_DUTY_BOUND 100.0
#define R_DUTY_BOUND 100.0

// period max and min values
#define L_MTR_MIN 0
#define L_MTR_MAX 3200
#define R_MTR_MIN 0
#define R_MTR_MAX 3200


// Interface functions
    
/**
 * Set up the PIC PWM module.
 */
void init_pwm();

/**
 * Turn on PWM. 
 */
void enable_pwm();

/**
 * Stop all PWM operations.
 */
void disable_pwm();


/**
 * @brief Set the PWM duty cycle for the left motor.
 *        The correct duty is set regardless of the direction.
 * @param duty The duty cycle as a value between -1.0 and 1.0
 */
void set_pwm_duty_l(long double duty);


/**
 * @brief Set the PWM duty cycle for the right motor.
 *        The correct duty is set regardless of the direction.
 * @param duty The duty cycle as a value between -1.0 and 1.0.
 */
void set_pwm_duty_r(long double duty);


#ifdef	__cplusplus
}
#endif

#endif	// MICROMOUSE_PIC_PWM_H_

