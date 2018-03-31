/**
 * File:
 *     encoder.c
 *
 * Description:
 *     Hardware level functions for interacting with the encoder.
 *
 * Notes:
 *     Before any functions are used, the init function must be called.
 *
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>

#include "micromouse/pic/components/encoder.h"

void init_encoder() {
    // Set encoder ports to inputs.
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB8 = 1;
}

