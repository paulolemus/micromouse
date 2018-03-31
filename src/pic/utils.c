/**
 * File:
 *     utils.c
 *
 * Description:
 *     Implementation for utils.h.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>

#include "micromouse/config.h"
#include "micromouse/pic/utils.h"

static volatile unsigned int tmr_3_ticks;

void wait_ms(const unsigned int ms) {
    tmr_3_ticks = 0;
    // Wait uses tmr 3.
    T3CONbits.TCKPS = 0b11; // 256 pre, 32000000 / 256 == 125000
    TMR3 = 0;
    PR3 = 125; // 1 ms == 125000 Hz / 1000

    // Configure and enable interrupt
    IPC2bits.T3IP = 4; // lvl 4 priority
    IFS0bits.T3IF = 0; // Clear interrupt flag
    IEC0bits.T3IE = 1; // Enable interrupts
    
    // Enable timer
    T3CONbits.TON = 1;
    
    // Wait for tmr 3 to finish.
    while(tmr_3_ticks < ms);
    
    // Clear interrupts and state
    IEC0bits.T3IE = 0;
    IFS0bits.T3IF = 0;
    T3CONbits.TON = 0;
}


void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void) {
    IFS0bits.T3IF = 0;
    tmr_3_ticks++;
}
