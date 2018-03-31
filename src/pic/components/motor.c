/**
 * File:
 *     motor.c
 *
 * Description:
 *     Hardware level functions for interacting with the motors.
 *
 * Notes:
 *     Before any functions are used, the init function must be called.
 *     The mouse has two DC motors.
 *
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>

#include "micromouse/pic/components/motor.h"

void init_motor() {
    // Set the motor PWM and direction pins to be outputs.
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;
    
    // Set outputs to 0
    LATBbits.LATB13 = 0; // Left direction control
    LATBbits.LATB12 = 0; // Left motor control
    LATBbits.LATB15 = 0; // Right direction control
    LATBbits.LATB14 = 0; // Motor pwm control
}

