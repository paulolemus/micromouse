/**
 * File:
 *     oscillator.c
 * 
 * Description:
 *     Implementation for oscillator.h header.
 * 
 * Notes:
 * 
 * 
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>

#include "micromouse/pic/components/oscillator.h"

void init_oscillator() {
    // 7.37 MHz nominal
    // Dvi by 0.0737, 6 down from 11.25
    // Fosc = 64 MHz
    // Fcy  = 32 MHz
    
    OSCTUNbits.TUN = 0b1100;   // FRC +9%, FRC = 8.0333 MHz
    PLLFBD = 30;               // PLL multiplier N+2 (128) M
    CLKDIVbits.PLLPOST = 0b00; // Output divider div_2
}