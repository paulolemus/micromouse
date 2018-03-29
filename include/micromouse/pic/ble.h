/**
 * File:
 *     ble.h
 *
 * Description:
 *     The interface for communication over the Bluetooth Low Energy module.
 *     This file provides functions used for setting up, interacting with, and
 *     disconnecting from an external device via text messages.
 *     The BLE module is an RN4871 Bluetooth 4.2 Low-Energy module.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */    

#ifndef MICROMOUSE_PIC_BLE_H_
#define MICROMOUSE_PIC_BLE_H_

#ifdef	__cplusplus
extern "C" {
#endif


// Interface functions
    
/**
 * Setup all software modules required by BLE.
 */
void init_ble();

/**
 * Turn on the BLE communication channels.
 */
void enable_ble();

/**
 * Stop all BLE operations.
 */
void disable_ble();


#ifdef	__cplusplus
}
#endif

#endif	// MICROMOUSE_PIC_BLE_H_

