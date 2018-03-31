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
#include <stdbool.h>

// Hardware components
#include "micromouse/pic/components/oscillator.h"
#include "micromouse/pic/components/led.h"
#include "micromouse/pic/components/sensor.h"
#include "micromouse/pic/components/encoder.h"
#include "micromouse/pic/components/motor.h"

// Hardware interface modules
#include "micromouse/pic/adc.h"
#include "micromouse/pic/ble.h"
#include "micromouse/pic/qei.h"
#include "micromouse/pic/pwm.h"
#include "micromouse/pic/motor_control.h"

#include "micromouse/pic/utils.h"

///
/// Testing functions, for DEBUGGING ONLY
///

void test_leds() {
    // LEDs work! Uncomment to view.
    // Consider disabling ADC module, as it may use the LEDs.
    //LED_ON(RGB_R);
    //LED_ON(RGB_G);
    //LED_ON(RGB_B);
    //LED_ON(LED_L);
    //LED_ON(LED_R);
}

void test_emitters() {
    // Test emitters! working perfectly.
    //EMI_ON(EMI_RR);
    //EMI_ON(EMI_LL);
    //EMI_ON(EMI_RF);
    //EMI_ON(EMI_LF);
    
    //EMI_OFF(EMI_RR);
    //EMI_OFF(EMI_LL);
    //EMI_OFF(EMI_RF);
    //EMI_OFF(EMI_LF);
}

void test_motors() {
    // Right motor drive test
    TRISBbits.TRISB15 = 0; // Right motor direction pin is an output.
    TRISBbits.TRISB14 = 0; // Right motor PWM pin is output.
    // Left motor drive test
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;
    
    LATBbits.LATB13 = 0; // Left direction control
    LATBbits.LATB12 = 0; // Left motor control
    LATBbits.LATB15 = 0; // Right direction control
    LATBbits.LATB14 = 0; // Motor pwm control
    
    
    // Left behavior: (pwm, dir)
    // 0, 0 = nothing
    // 1, 0 = forward
    // 0, 1 = backwards
    // 1, 1 = nothing
    
    // Right behavior: (pwm, dir)
    // 0, 0 = nothing
    // 1, 0 = backwards
    // 0, 1 = forward
    // 1, 1 = nothing
}

void test_qei() {
    
    signed long long l_qei = 0;
    signed long long r_qei = 0;
    signed long long l_qei_last = 0;
    signed long long r_qei_last = 0;
    
    
    while(true) {
        wait_ms(2);
        l_qei_last = l_qei;
        r_qei_last = r_qei;
        l_qei = get_qei_l_pos();
        r_qei = get_qei_r_pos();
        
        if(l_qei >= l_qei_last) {
            LED_ON(LED_L);
        } else {
            LED_OFF(LED_L);
        }
        
        if(r_qei >= r_qei_last) {
            LED_ON(LED_R);
        } else {
            LED_OFF(LED_R);
        }
    }
}

void test_motor_control_positional() {
    wait_ms(1000);
    update_mc_state();
    init_position_mc();
    set_motor_control_function(&position_mc);
    enable_motor_control();
    while(true) {
        
    }
}

void test_left() {
    wait_ms(1000);
    update_mc_state();
    init_left_mc();
    set_motor_control_function(&left_mc);
    enable_motor_control();
    while(true);
}

void test_right() {
    wait_ms(1000);
    update_mc_state();
    init_right_mc();
    set_motor_control_function(&right_mc);
    enable_motor_control();
    while(true);
}

void test_around() {
    wait_ms(1000);
    update_mc_state();
    init_around_mc();
    set_motor_control_function(&around_mc);
    enable_motor_control();
    while(true);
}

void test_mc_straight() {
    init_straight_mc();
    set_motor_control_function(&straight_mc);
    
    while(true) {
        wait_mc();
        update_mc_state();
        straight_mc();
    }
}

void test_mc_track() {
    init_track_mc();
    set_motor_control_function(&track_mc);
    
    while(true) {
        //
    }
}


int main(int argc, char** argv) {
    
    // Initialize hardware components
    init_oscillator();
    init_led();
    init_sensor();
    init_encoder();
    init_motor();
    
    // Initialize software modules
    init_adc();
    //init_ble();
    init_qei();
    init_pwm();
    init_motor_control();
    
    // Enable desired software modules
    enable_adc();
    //enable_ble();
    enable_qei();
    enable_pwm();
    
    
    // TESTING FUNCTIONS
    //test_leds();
    //test_emitters();
    //test_motors();
    //test_qei();
    //test_motor_control_positional();
    //test_left();
    //test_right();
    test_around();
    //test_mc_straight();
    //test_mc_track();
    
    while(true) {
        // Do nothing
    }
    return (EXIT_SUCCESS);
}

