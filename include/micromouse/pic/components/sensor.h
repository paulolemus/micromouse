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


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_PIC_COMPONENTS_SENSOR_H_
