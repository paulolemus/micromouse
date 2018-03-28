/**
 * File:   
 *     pic_hardware_test.c
 * 
 * Description:
 *     Testing driver used comprehensive testing of hardware components.
 * 
 * Notes:
 * 
 * 
 * Author: 
 *     Paulo Lemus
 */

// DSPIC33FJ128MC804 Configuration Bit Settings

// 'C' source line config statements

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Mode (Internal Fast RC (FRC) w/ PLL)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

// Hardware components
#include "micromouse/pic/components/oscillator.h"
#include "micromouse/pic/components/led.h"
#include "micromouse/pic/components/sensor.h"
#include "micromouse/pic/components/encoder.h"
#include "micromouse/pic/components/motor.h"

// Hardware interface modules
#include "micromouse/pic/adc.h"


int main(int argc, char** argv) {
    
    // Initialize hardware components
    init_oscillator();
    init_led();
    init_sensor();
    //init_encoder();
    //init_motor();
    
    // Right motor drive test
    TRISBbits.TRISB15 = 0; // Right motor direction pin is an output.
    TRISBbits.TRISB14 = 0; // Right motor PWM pin is output.
    // Left motor drive test
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;
    
    // Initialize software modules
    //init_adc();
    //enable_adc();
    
    // LEDs work! Uncomment to view, also disable ADC module.
    //LED_ON(RGB_R);
    //LED_ON(RGB_G);
    //LED_ON(RGB_B);
    LED_ON(LED_L);
    //LED_ON(LED_R);
    
    // Test emitters! working perfectly.
    //EMI_ON(EMI_RR);
    //EMI_ON(EMI_LL);
    //EMI_ON(EMI_RF);
    //EMI_ON(EMI_LF);
    
    //EMI_OFF(EMI_RR);
    //EMI_OFF(EMI_LL);
    //EMI_OFF(EMI_RF);
    //EMI_OFF(EMI_LF);
    
    LATBbits.LATB13 = 1; // Left direction control
    LATBbits.LATB12 = 0; // Left motor control
    LATBbits.LATB15 = 1; // Right direction control
    LATBbits.LATB14 = 1; // Motor pwm control

    while(1) {
        // Do nothing
    }
    return (EXIT_SUCCESS);
}

