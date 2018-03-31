/**
 * File:
 *     adc.c
 *
 * Description:
 *     Implementation for adc.h.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>
#include <stddef.h>

#include "micromouse/config.h"
#include "micromouse/pic/adc.h"
#include "micromouse/pic/components/led.h"
#include "micromouse/pic/components/sensor.h"

// ADC macros

// Detector IDs
#define DET_LL 6
#define DET_LF 7
#define DET_RR 5
#define DET_RF 4

#define NUM_DETECTORS 4

// Select the detector to autoscan with the dsPIC.
#define SELECT_DET(detector_id) (AD1CHS0bits.CH0SA = detector_id)
#define CAPTURE_SCAN(scans, idx) (scans[idx] = ADC1BUF0)

// Internal variables

// Sensor reading storage
// The sensor readings are always a running average
static volatile unsigned int ll_scans[ADC_AVG] = {0};
static volatile unsigned int lf_scans[ADC_AVG] = {0};
static volatile unsigned int rr_scans[ADC_AVG] = {0};
static volatile unsigned int rf_scans[ADC_AVG] = {0};

// Detector calibration variables
static unsigned int ll_close = DEFAULT_LL_CLOSE;
static unsigned int lf_close = DEFAULT_LF_CLOSE;
static unsigned int rr_close = DEFAULT_RR_CLOSE;
static unsigned int rf_close = DEFAULT_RF_CLOSE;

// Out of the ADC_AVG retained scans, this is the index to save it in.
static volatile unsigned int adc_scan_index = 0;
// Index of the sensor to scan.
static volatile unsigned int adc_sensor_rotation = 0;


/*
 * The ADC clock is derived from system clock (Fcy = 32MHz),
 * as defined in oscillator.c.
 * This means Tcy = 31.25 ns.
 */
void init_adc() {
    
    // Set AN4/5/6/7 to analog control, rest to digital control
    AD1PCFGL = 0b100001111;
    
    // Configure ADC software module
    AD1CON1bits.ADON = 0;       // Disable to configure
    AD1CON1bits.AD12B = 1;      // Operate in 12 bit mode (4096 max)
    AD1CON1bits.SSRC = 0b111;   // Enable auto-convert of a sample
    
    AD1CON3bits.ADCS = 9;       // 10 * Tcy = TAD = 312.5 ns
    AD1CON3bits.SAMC = 0b11111; // 31 TAD for auto sample time = 10uS
    
    // Configure finish of conversion interrupts
    IPC3bits.AD1IP = 6;         // lvl 6 priority
    IEC0bits.AD1IE = 0;         // Disable interrupts
    
    
    // Configure Timer for sampling and converting ADC
    T4CONbits.TCKPS = 0b01;     // 1:8 prescaler, ticks at 4,000,000Hz, 0.25 us
    TMR4 = 0;                   // Clear TMR4 counter
    PR4 = ADC_DT * 4;           // Interrupts every ADC_DT microseconds.
    
    // Configure TIMER 4 interrupts
    IPC6bits.T4IP = 5;          // lvl 6 priority (second highest)
    IFS1bits.T4IF = 0;          // Clear IF
    IEC1bits.T4IE = 0;          // Enable Tmr4 interrupts
    T4CONbits.TON = 0;          // Turn off timer4  
}

void enable_adc() {
    size_t i;
    
    // Clear interrupt flag and enable interrupts.
    IFS0bits.AD1IF = 0; // Clear flag bit
    IEC0bits.AD1IE = 1; // Enable conversion interrupts
    
    // Clear interrupt flags and enable interrupts for timer.
    IFS1bits.T4IF = 0; // Clear IF
    IEC1bits.T4IE = 1; // Enable Tmr4 interrupts
    
    // Set state of global variables
    for(i = 0; i < ADC_AVG; ++i) {
        ll_scans[i] = 0;
        lf_scans[i] = 0;
        rr_scans[i] = 0;
        rf_scans[i] = 0;
    }
    adc_scan_index = 0;
    adc_sensor_rotation = 0;
    
    // Turn on emitters
    // TODO: Remove this portion
    EMI_ON(EMI_LL);
    EMI_ON(EMI_LF);
    EMI_ON(EMI_RR);
    EMI_ON(EMI_RF);
    
    // Select first sensor in rotation
    // Rotation goes ll, lr, rr, rf
    SELECT_DET(DET_LL);
    
    
    T4CONbits.TON = 1; // Turn on timer4  
    AD1CON1bits.ADON = 1; // Turn on
}

void disable_adc() {
    // Disable modules
    T4CONbits.TON = 0; // Turn off timer4  
    AD1CON1bits.ADON = 0; // Turn off
    
    // Disable interrupts
    IEC0bits.AD1IE = 0; // Disable conversion interrupts
    IEC1bits.T4IE = 0;  // Disable Tmr4 interrupts
    
    // Turn off emitters
    EMI_OFF(EMI_LL);
    EMI_OFF(EMI_LF);
    EMI_OFF(EMI_RR);
    EMI_OFF(EMI_RF);
}

unsigned int get_scan_ll() {
    size_t i;
    unsigned sum = 0;
    
    for(i=0; i < ADC_AVG; ++i) {
        sum += ll_scans[i];
    }
    return sum / (ADC_AVG);
}

unsigned int get_scan_lf() {
    size_t i;
    unsigned sum = 0;
    
    for(i=0; i < ADC_AVG; ++i) {
        sum += lf_scans[i];
    }
    return sum / (ADC_AVG);
}

unsigned int get_scan_rr() {
    size_t i;
    unsigned sum = 0;
    
    for(i=0; i < ADC_AVG; ++i) {
        sum += rr_scans[i];
    }
    return sum / (ADC_AVG);
}

unsigned int get_scan_rf() {
    size_t i;
    unsigned sum = 0;
    
    for(i=0; i < ADC_AVG; ++i) {
        sum += rf_scans[i];
    }
    return sum / (ADC_AVG);
}

unsigned int get_close_ll() {
    return ll_close;
}
unsigned int get_close_lf() {
    return lf_close;
}
unsigned int get_close_rr() {
    return rr_close;
}
unsigned int get_close_rf() {
    return rf_close;
}


// Timer used to start ADC scans of all detectors.
// Every ADC_DT us, all the detectors are 
void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T4Interrupt(void) {
    IFS1bits.T4IF = 0; // clear T4 interrupt flag

    // Begin a conversion cycle every ADT_DT time period.
    AD1CON1bits.SAMP = 1;
}



// Interrupt to save values from the four detectors once conversions finished.
// Order of scan goes: ll, lf, rr, rf
void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _ADC1Interrupt(void) {
    IFS0bits.AD1IF = 0; // Clear conversion flag

    // Capture value from scan depending on adc rotation
    switch(adc_sensor_rotation) {
        case 0: CAPTURE_SCAN(ll_scans, adc_scan_index); break;
        case 1: CAPTURE_SCAN(lf_scans, adc_scan_index); break;
        case 2: CAPTURE_SCAN(rr_scans, adc_scan_index); break;
        case 3: CAPTURE_SCAN(rf_scans, adc_scan_index); break;
    }
    
    // Rotate to next scan
    adc_sensor_rotation = (adc_sensor_rotation + 1) % NUM_DETECTORS;
    
    // If we have scanned all the sensors, we have finished this batch and the
    // scan index can increment.
    if(adc_sensor_rotation == 0) {
        adc_scan_index = (adc_scan_index + 1) % ADC_AVG;
    }
    
    // Move to next scan
    switch(adc_sensor_rotation) {
        case 0: SELECT_DET(DET_LL); break;
        case 1: SELECT_DET(DET_LF); AD1CON1bits.SAMP = 1; break;
        case 2: SELECT_DET(DET_RR); AD1CON1bits.SAMP = 1; break;
        case 3: SELECT_DET(DET_RF); AD1CON1bits.SAMP = 1; break;
    }
    
    // Check if ll is working
    if(get_scan_ll() > ll_close) {
        //LED_ON(LED_L);
    }
    else {
        //LED_OFF(LED_L);
    }
    // Check if lf is working - GOOD
    if(get_scan_lf() > lf_close) {
        //LED_ON(LED_L);
    } else {
        //LED_OFF(LED_L);
    }
    // Check if rr is working - GOOD
    if(get_scan_rr() > rr_close) {
        //LED_ON(LED_R);
    } else {
        //LED_OFF(LED_R);
    }
    // Check if rf is working - GOOD
    if(get_scan_rf() > rf_close) {
        //LED_ON(LED_R);
    } else {
        //LED_OFF(LED_R);
    }
}
