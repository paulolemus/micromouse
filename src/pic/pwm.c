/**
 * File:
 *     pwm.c
 *
 * Description:
 *     Implementation for pwm.h.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>
#include <math.h>

#include "micromouse/pic/pwm.h"
#include "micromouse/pic/components/motor.h"


void init_pwm() {
    P1TCONbits.PTEN = 0;    // Disable PWM time base
    
    PWM1CON1bits.PMOD1 = 1; // Independent output mode
    PWM1CON1bits.PMOD2 = 1; // Independent output mode
    PWM1CON1bits.PEN1H = 0; // Disable PWM on pin
    PWM1CON1bits.PEN1L = 0; // Disable PWM on pin
    PWM1CON1bits.PEN2H = 0; // Disable PWM on pin
    PWM1CON1bits.PEN2L = 0; // Disable PWM on pin
    
    PWM1CON2bits.IUE = 1;   // Updated to PxDC reg is immediate
    
    P1TPER = 1599;          // Fcy / Fpwm-1 -> 32MHz / 20kHz-1 = 1599
    
    P1TMRbits.PTMR = 0;     // Reset count to 0
    
    set_pwm_duty_l(0.0);    // Set duty cycle to 0%.
    set_pwm_duty_r(0.0);    // Set duty cycle to 0%.
}


void enable_pwm() {
    P1TMRbits.PTMR = 0;     // Reset count to 0
    P1TCONbits.PTEN = 1;    // Turn on PWM time base
    
    PWM1CON1bits.PMOD1 = 1; // Independent output mode
    PWM1CON1bits.PMOD2 = 1; // Independent output mode
    PWM1CON1bits.PEN2H = 1; // PWM1H2 enabled for PWM left
    PWM1CON1bits.PEN1H = 1; // PWM1H1 enabled for PWM right
    
    L_MTR_DIR = L_MTR_FWD;
    R_MTR_DIR = R_MTR_FWD;
    
    set_pwm_duty_l(0.0);    // Set duty cycle to 0%.
    set_pwm_duty_r(0.0);    // Set duty cycle to 0%.
}


void disable_pwm() {
    P1TCONbits.PTEN = 0;    // Disable PWM time base
    PWM1CON1bits.PEN2H = 0; // PWM1H2 disabled for PWM left
    PWM1CON1bits.PEN1H = 0; // PWM1H1 disabled for PWM right
}


void set_pwm_duty_l(double duty) {
    
    signed int period;
    
    // Normalize and bound
    duty = duty / L_DUTY_BOUND;
    if(duty > 1.0)       duty = 1.0;
    else if(duty < -1.0) duty = -1.0;
    
    if(duty >= 0) {
        L_MTR_DIR = L_MTR_FWD;
        period = (signed int) (fabs(duty) * L_MTR_MAX);
    } else {
        L_MTR_DIR = L_MTR_REV;
        period = 
            (signed int) L_MTR_MAX 
            - ((signed int) (fabs(duty) * L_MTR_MAX));
    }
    
    if     (period < L_MTR_MIN) period = L_MTR_MIN;
    else if(period > L_MTR_MAX) period = L_MTR_MAX;
    L_MTR_PER = (unsigned int) period;
}

void set_pwm_duty_r(double duty) {
    
    signed int period;
    
    // Normalize and bound
    duty = duty / R_DUTY_BOUND;
    if(duty > 1.0)       duty = 1.0;
    else if(duty < -1.0) duty = -1.0;
    
    if(duty >= 0) {
        R_MTR_DIR = R_MTR_FWD;
        period = 
            (signed int) R_MTR_MAX
            - ((signed int) (fabs(duty) * R_MTR_MAX));
    } else {
        R_MTR_DIR = R_MTR_REV;
        period = (signed int) (fabs(duty) * R_MTR_MAX);
    }
    
    if     (period < R_MTR_MIN) period = R_MTR_MIN;
    else if(period > R_MTR_MAX) period = R_MTR_MAX;
    R_MTR_PER = (unsigned int) period;
}