/**
 * File:
 *     led.c
 * 
 * Description:
 *     Implementation for led.h header.
 * 
 * Notes:
 * 
 * 
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>

#include "micromouse/pic/components/led.h"

void init_led() {
    // Set LED ports to outputs
    
    // RGB
    TRISAbits.TRISA9 = 0; // R
    TRISCbits.TRISC3 = 0; // G
    TRISCbits.TRISC4 = 0; // B
    
    // LED
    TRISAbits.TRISA4 = 0; // Left signal
    TRISCbits.TRISC5 = 0; // Right signal
}
