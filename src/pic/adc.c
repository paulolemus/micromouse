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

#define CAPTURE_SCAN(sensor_var) (sensor_var = (sensor_var + ADC1BUF0) / 2)

// Internal variables

// Sensor reading storage
static volatile unsigned int ll_val;
static volatile unsigned int lf_val;
static volatile unsigned int rr_val;
static volatile unsigned int rf_val;

// Previous sensor reading storage
static volatile unsigned int ll_last;
static volatile unsigned int lf_last;
static volatile unsigned int rr_last;
static volatile unsigned int rf_last;

// Detector calibration variables TODO: FIX INITIAL VALUES
static unsigned int ll_close = 600;
static unsigned int lf_close = 600;
static unsigned int rr_close = 600;
static unsigned int rf_close = 600;

//static unsigned int ll_far = 300;
//static unsigned int lf_far = 300;
//static unsigned int rr_far = 300;
//static unsigned int rf_far = 300;

// Number of MS to wait before starting a new scanning sequence.
static volatile unsigned int tmr_4_ticks;
// ADC scan rotation
static volatile unsigned int adc_rotation;




void init_adc() {
    
    // Set AN4/5/6/7 to analog control, rest to digital control
    AD1PCFGL = 0b100001111;
    
    // Configure ADC software module
    AD1CON1bits.ADON = 0; // Disable to configure
    AD1CON1bits.SSRC = 0b111; // End sample after internal counter time
    
    AD1CON2bits.BUFM = 1; // Fill buffer from 0x0
    
    AD1CON3bits.SAMC = 2; // 2 TAD for auto sample time
    AD1CON3bits.ADCS = 2; // 3 * Tcy = TAD, used for auto conversion
    
    // Configure finish of conversion interrupts
    IPC3bits.AD1IP = 6; // lvl 6 priority
    IEC0bits.AD1IE = 0; // Disable interrupts
    
    
    // Configure Timer for sampling and converting ADC
    T4CONbits.TCKPS = 0b10; // 1:64 prescaler, ticks at 500000 Hz
    TMR4 = 0; // Clear TMR4 counter
    PR4 = 500; // Overflows every 1 ms (500000 / 1000) == 500 == 1 ms
    tmr_4_ticks = 0;
    
    // Configure TIMER 4 interrupts
    IPC6bits.T4IP = 5; // lvl 6 priority (second highest)
    IFS1bits.T4IF = 0; // Clear IF
    IEC1bits.T4IE = 0; // Enable Tmr4 interrupts
    T4CONbits.TON = 0; // Turn off timer4  
}

void enable_adc() {
    // Clear interrupt flag and enable interrupts.
    IFS0bits.AD1IF = 0; // Clear flag bit
    IEC0bits.AD1IE = 1; // Enable conversion interrupts
    
    // Clear interrupt flags and enable interrupts for timer.
    IFS1bits.T4IF = 0; // Clear IF
    IEC1bits.T4IE = 1; // Enable Tmr4 interrupts
    
    // Set state of global variables
    ll_val = 0;
    lf_val = 0;
    rr_val = 0; 
    rf_val = 0;
    tmr_4_ticks = 0;
    adc_rotation = 0;
    
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

unsigned get_det_ll() {
    return ll_val;
}

unsigned get_det_lf() {
    return lf_val;
}

unsigned get_det_rr() {
    return rr_val;
}

unsigned get_det_rf() {
    return rf_val;
}


// Timer used to start ADC scans of all detectors - operates at 2x PID speed
void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T4Interrupt(void) {
    IFS1bits.T4IF = 0; // clear T4 interrupt flag

    tmr_4_ticks++;
    
    if(tmr_4_ticks == ADC_DT) {
        tmr_4_ticks = 0;

        // Save last values
        ll_last = ll_val;
        lf_last = lf_val;
        rr_last = rr_val;
        rf_last = rf_val;
        
        // Convert here
        AD1CON1bits.SAMP = 1;
    }
}



// Interrupt to save values from the four detectors once conversions finished.
// Order of scan goes: ll, lf, rr, rf
void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _ADC1Interrupt(void) {
    IFS0bits.AD1IF = 0; // Clear conversion flag

    // Capture value from scan depending on adc rotation
    switch(adc_rotation) {
        case 0: CAPTURE_SCAN(ll_val); break;
        case 1: CAPTURE_SCAN(lf_val); break;
        case 2: CAPTURE_SCAN(rr_val); break;
        case 3: CAPTURE_SCAN(rf_val); break;
    }
    
    // Rotate to next scan
    adc_rotation = (adc_rotation + 1) % NUM_DETECTORS;
    
    // Move to next scan
    switch(adc_rotation) {
        case 0: SELECT_DET(DET_LL); break;
        case 1: SELECT_DET(DET_LF); AD1CON1bits.SAMP = 1; break;
        case 2: SELECT_DET(DET_RR); AD1CON1bits.SAMP = 1; break;
        case 3: SELECT_DET(DET_RF); AD1CON1bits.SAMP = 1; break;
    }
    
    // Check if ll is working
    if(ll_val > ll_close) {
        LED_ON(LED_L);
    }
    else {
        LED_OFF(LED_L);
    }
    // Check if lf is working - GOOD
    if(lf_val > lf_close) {
        LED_ON(RGB_G);
    } else {
        LED_OFF(RGB_G);
    }
    // Check if rr is working - GOOD
    if(rr_val > rr_close) {
        LED_ON(LED_R);
    } else {
        LED_OFF(LED_R);
    }
    // Check if rf is working - GOOD
    if(rf_val > rf_close) {
        LED_ON(RGB_B);
    } else {
        LED_OFF(RGB_B);
    }
}
