/**
 * File:
 *     qei.h
 *
 * Description:
 *     The QEI module allows us to determine how far the mouse has moved from
 *     a prior position.
 *     This is the interface for the QEI module.
 *
 * Notes:
 *     There is one massive error with the current design.
 *     Unfortunately, only one module at a time is able to read the QEI values.
 *     This is because when ever a read is made, the old value is saved and used
 *     in the next read.
 *     Simply be careful not to read the values say the motor control module
 *     AND from the main at the same time.
 *
 *     One way around this might be to define a QEI struct that would hold data.
 *     This way, each module that wants to use QEI can with their own struct.
 *     Each module would have its own "instance" of the QEI module.
 *
 * Author:
 *     Paulo Lemus
 */    

#ifndef MICROMOUSE_PIC_QEI_H_
#define MICROMOUSE_PIC_QEI_H_

#ifdef	__cplusplus
extern "C" {
#endif


// Interface functions
    
/**
 * Setup all software modules required by QEI.
 */
void init_qei();

/**
 * Turn on the QEI module.
 * This module is entirely self regulating.
 */
void enable_qei();

/**
 * Disable all QEI operations.
 */
void disable_qei();

/**
 * Getters for qei readings.
 * These functions return the distance the wheels have moved from their
 * previous readings.
 * The "l" funciton gets the reading for the left module.
 * The "r" function gets the readings for the right module.
 */
signed int get_qei_l();
signed int get_qei_r();


#ifdef	__cplusplus
}
#endif

#endif	// MICROMOUSE_PIC_QEI_H_
