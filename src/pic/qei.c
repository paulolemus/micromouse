/**
 * File:
 *     qei.c
 *
 * Description:
 *     Implementation for qei.h.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>

#include "micromouse/pic/qei.h"
#include "micromouse/pic/components/led.h"

///
/// QEI internal macros
///

// Left and right position register
#define L_QEI_CNT POS1CNT
#define R_QEI_CNT POS2CNT

// Left and right reset max
#define L_QEI_MAX MAX1CNT 
#define R_QEI_MAX MAX2CNT 

// One rotation of the left and right motor
#define L_QEI_ROT 2100
#define R_QEI_ROT 2100


///
/// Internal variables
///

// Overflows counters
static volatile signed long long l_overflows = 0;
static volatile signed long long r_overflows = 0;


void init_qei() {
    // Set QEI pins in PPS (Peripheral Pin Select).
    RPINR14bits.QEA1R = 5;
    RPINR14bits.QEB1R = 6;
    RPINR16bits.QEA2R = 7;
    RPINR16bits.QEB2R = 8;

    // Init QEI software module.
    QEI1CONbits.QEIM = 0;     // Use 2x mode without indx/updn pins.
    QEI2CONbits.QEIM = 0;     // Use 2x mode without indx/updn pins.

    QEI1CONbits.UPDN = 1;     // Position counter direction is +
    QEI2CONbits.UPDN = 1;     // Position counter direction is +

    DFLT1CONbits.CEID = 1;    // Disable count error interrupts.
    DFLT2CONbits.CEID = 1;    // Disable count error interrupts.

    QEI1CONbits.SWPAB = 1;    // QEI1 swap so driving forward is +.
    QEI2CONbits.SWPAB = 0;    // QEI1 swap so driving forward is +.

    L_QEI_CNT = 0;            // Reset position counter to 0.
    R_QEI_CNT = 0;            // Reset position counter to 0.

    L_QEI_MAX = L_QEI_ROT;    // Reset and interrupt every wheel rotation.
    R_QEI_MAX = R_QEI_ROT;    // Reset and interrupt every wheel rotation.

	// QEI Interrupt setup
    IEC3bits.QEI1IE = 0;      // Disable interrupts
    IEC4bits.QEI2IE = 0;      // Disable interrupts
    IPC14bits.QEI1IP = 4;     // Priority lvl4
    IPC18bits.QEI2IP = 4;     // Priority lvl4
    IFS3bits.QEI1IF = 0;      // Clear flag
    IFS4bits.QEI2IF = 0;      // Clear flag

    // Reset global state variables.
    l_overflows = 0;
    r_overflows = 0;
}

void enable_qei() {
    // Reset global state variables.
    l_overflows = 0;
    r_overflows = 0;

	// Clear flags, enable QEI interrupts.
    IFS3bits.QEI1IF = 0;      // Clear flag
    IFS4bits.QEI2IF = 0;      // Clear flag
    IEC3bits.QEI1IE = 1;      // Enable interrupts
    IEC4bits.QEI2IE = 1;      // Enable interrupts

    // Enable QEI software module.
    QEI1CONbits.QEIM = 0b101; // Use 2x mode without indx/updn pins.
    QEI2CONbits.QEIM = 0b101; // Use 2x mode without indx/updn pins.
}

void disable_qei() {
	// Clear flags, enable QEI interrupts.
    IEC3bits.QEI1IE = 0;      // Disable interrupts
    IEC4bits.QEI2IE = 0;      // Disable interrupts
    IFS3bits.QEI1IF = 0;      // Clear flag
    IFS4bits.QEI2IF = 0;      // Clear flag

    // Disable QEI software module.
    QEI1CONbits.QEIM = 0;     // Disable qei and internal qei timer. 
    QEI2CONbits.QEIM = 0;     // Disable qei and internal qei timer. 
}


signed long long get_qei_l_pos() {
    signed long long l_pos = l_overflows * L_QEI_ROT;
    if(l_pos >= 0) {
        l_pos += L_QEI_CNT;
    } else {
        l_pos += L_QEI_CNT - 1;
    }
    return l_pos;
}

signed long long get_qei_r_pos() {
    signed long long r_pos = r_overflows * R_QEI_ROT;
    if(r_pos >= 0) {
        r_pos += R_QEI_CNT;
    } else {
        r_pos += R_QEI_CNT - 1;
    }
    return r_pos;
}


// QEI overflow interrupt for left motor.
// This interrupt gets called on any overflows and underflows.
void __attribute__((__interrupt__, no_auto_psv)) _QEI1Interrupt(void) {
	IFS3bits.QEI1IF = 0; // Clear interrupt flag.

    if(L_QEI_CNT > L_QEI_ROT / 2) {
        // QEI underflowed.
        l_overflows--;
    } else {
        // QEI overflowed.
        l_overflows++;
    }
}


// QEI2 overflow interrupt for right motor.
// This interrupt gets called on any overflows and underflows.
void __attribute__((__interrupt__, no_auto_psv)) _QEI2Interrupt(void) {
	IFS4bits.QEI2IF = 0; // Clear interrupt flag.

    if(R_QEI_CNT > R_QEI_ROT / 2) {
        // QEI underflowed.
        r_overflows--;
    } else {
        // QEI overflowed.
        r_overflows++;
    }
}
