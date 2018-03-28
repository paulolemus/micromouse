/**
 * File:
 *     sensor.c
 * 
 * Description:
 *     Implementation for sensor.h header.
 * 
 * Notes:
 * 
 * 
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>

#include "micromouse/pic/components/sensor.h"

void init_sensor() {
    // Set emitter ports to outputs
    TRISAbits.TRISA8 = 0; // EMI_LL 
    TRISBbits.TRISB4 = 0; // EMI_LF
    TRISAbits.TRISA3 = 0; // EMI_RR 
    TRISAbits.TRISA2 = 0; // EMI_RF 
    
    // The four detector pins are set to input by default.
}
