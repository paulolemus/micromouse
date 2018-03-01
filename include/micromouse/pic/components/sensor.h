/**
 * File:
 *     sensor.h
 *
 * Description:
 *     Hardware level functions for interacting with the sensors.
 *
 * Notes:
 *     Before any functions are used, the init function must be called.
 *     There are four IR detectors and four IR emitters.
 *
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_PIC_COMPONENTS_SENSOR_H_
#define MICROMOUSE_PIC_COMPONENTS_SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the IR detectors and emitters in hardware.
 *        Must be called before interacting with these sensors.
 */
void init_sensor();


// Emitter PORTS
// The emitters pins are digital out. 
#define EMI_LL LATAbits.LATA8
#define EMI_LF LATBbits.LATB4
#define EMI_RR LATAbits.LATA3
#define EMI_RF LATAbits.LATA2

// Emitter interaction macros
#define EMI_ON(emi_lat)  emi_lat = 1
#define EMI_OFF(emi_lat) emi_lat = 0


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_PIC_COMPONENTS_SENSOR_H_
