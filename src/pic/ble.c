/**
 * File:
 *     ble.c
 *
 * Description:
 *     Implementation for ble.h.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>

#include "micromouse/pic/ble.h"


// BLE enable pin definitions
#define BLE_MODULE_TRIS TRISCbits.TRISC6
#define BLE_MODULE_LAT  LATCbits.LATC6

// BLE toggle utilities
#define BLE_MODULE_ON(mod_lat) mod_lat = 1
#define BLE_MODULE_OFF(mod_lat) mod_lat = 0

void init_ble() {

    // Make BLE module enable pin a digital out.
    BLE_MODULE_TRIS = 0;
    
    // Assign UART U1RX pin to RP25.
    RPINR18bits.U1RXR = 25;
    // Assign UART U1TX pin to RP24.
    RPOR12bits.RP24R = 0b00011;
    
    // Run in Simplex mode (disable flow control)
    U1MODEbits.RTSMD = 1;
    
    // Set Baud rate - calculated with datasheet formula
    U1BRG = 16;
    
    // Disable interrupts and clear flags
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;
    // TODO: SET PRIORITY
}

void enable_ble() {
    
    // Turn on actual module.
    BLE_MODULE_ON(BLE_MODULE_LAT);
    
    // Enable interrupts and clear flags
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;
    IEC0bits.U1RXIE = 0; // TODO: enable
    IEC0bits.U1TXIE = 0; // TODO: enable
    
    // Enable UART module.
    U1MODEbits.UARTEN = 1;
    // Enable transmit capability.
    U1STAbits.UTXEN = 1;

}

void disable_ble() {
    
    // Disable transmit capability.
    U1STAbits.UTXEN = 0;
    // Disable UART module.
    U1MODEbits.UARTEN = 0;
    
    // Disable interrupts and clear flags
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;
    
    // Turn off actual module.
    BLE_MODULE_OFF(BLE_MODULE_LAT);
}
