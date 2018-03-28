/**
 * File:
 *     adc.h
 *
 * Description:
 *     The ADC module allows us to begin IR detector scans and retrieve
 *     their values in an async fashion.
 *     This is the interface for the ADC module.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */    

#ifndef MICROMOUSE_PIC_ADC_H_
#define MICROMOUSE_PIC_ADC_H_

#ifdef	__cplusplus
extern "C" {
#endif


// Interface functions
    
/**
 * Setup all software modules required by ADC.
 * This includes the ADC software module, the interrupt to handle conversions.
 */
void init_adc();

/**
 * Turn on ADC. The ADC module should be self regulating. It handles its own
 * operations in an interrupt. The data captured from the ADC modules can be
 * read through the getter functions found below.
 */
void enable_adc();

/**
 * Stop all ADC operations.
 */
void disable_adc();

/**
 * Getters for sensor readings.
 * If the ADC module is enabled, the readings are updated in realtime.
 * If the ADC module is disabled, then these functions return the last scan.
 */
unsigned get_scan_ll();
unsigned get_scan_lf();
unsigned get_scan_rr();
unsigned get_scan_rf();


#ifdef	__cplusplus
}
#endif

#endif	// MICROMOUSE_PIC_ADC_H_

