/**
 * File:
 *     motor_control.c
 *
 * Description:
 *     Implementation for motor_control.h.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */

#include <xc.h>
#include <math.h>

#include "micromouse/config.h"

#include "micromouse/core/pid.h"

#include "micromouse/pic/motor_control.h"
#include "micromouse/pic/adc.h"
#include "micromouse/pic/pwm.h"
#include "micromouse/pic/qei.h"
#include "micromouse/pic/utils.h"

#include "micromouse/pic/components/motor.h"
#include "micromouse/pic/components/led.h"


///
/// Global Internal State Variables
///

// Desired duty cycles
static volatile double l_duty = 0.0;
static volatile double r_duty = 0.0;

// QEI variables
static volatile signed long long l_pos = 0;
static volatile signed long long r_pos = 0;
static double l_vel = 0.0;
static double r_vel = 0.0;
static double l_acc = 0.0;
static double r_acc = 0.0;

// ADC
static volatile unsigned int scan_ll = 0;
static volatile unsigned int scan_lf = 0;
static volatile unsigned int scan_rr = 0;
static volatile unsigned int scan_rf = 0;

// Function to execute to control motors every update period.
static void (*volatile motor_control)(void);



void init_motor_control() {
    // Init timer 2 module.
    T2CONbits.TCKPS = 0b01; // 1:8 prescale, ticks at 4,000,000Hz, 0.25us.
    TMR2 = 0;               // Clear TMR2 counter
    PR2 = MC_DT * 4;        // Overflows every MC_DT microseconds.
    
    // Configure TMR2 Interrupts
    IPC1bits.T2IP = 5;      // lvl 6 priority
    IFS0bits.T2IF = 0;      // Clear IF flag
    IEC0bits.T2IE = 0;      // Disable interrupts
    
    // Set initial global state.
    l_duty = 0.0;
    r_duty = 0.0;
    set_motor_control_function(&position_mc);
}

void enable_motor_control() {
    // Turn on TMR2 module
    IFS0bits.T2IF = 0;      // Clear interrupt flag.
    IEC0bits.T2IE = 1;      // Enable TMR2 interrupts.
    T2CONbits.TON = 1;      // Turn on TMR2 module.
}

void disable_motor_control() {
    IEC0bits.T2IE = 0;      // Disable interrupts.
    T2CONbits.TON = 0;      // Turn off TMR2 module.
}

void set_motor_control_function(void (*motor_control_func)(void)) {
    motor_control = motor_control_func;
}


///
/// Motor Controller Functions
///

/**
 * The motors will hold their current positions.
 */
static signed long long position_mc_target_l = 0;
static signed long long position_mc_target_r = 0;
static signed int position_mc_prev_err_l = 0;
static signed int position_mc_prev_err_r = 0;
void init_position_mc() {
    // Function statics
    position_mc_target_l = l_pos;
    position_mc_target_r = r_pos;
    position_mc_prev_err_l = 0;
    position_mc_prev_err_r = 0;
    
    // Global statics
    l_duty = 0.0;
    r_duty = 0.0;
}
void position_mc() {
    const double kp = 0.1;
    const double kd = 0.0;
    
    // Calculate error in position
    const signed int l_err = (signed int) (l_pos - position_mc_target_l);
    const signed int r_err = (signed int) (r_pos - position_mc_target_r);
    
    // Calculate PID outputs
    const double p_out_l = p_term(l_err, kp);
    const double d_out_l = d_term(l_err, position_mc_prev_err_l, MC_DT, kd);
    const double p_out_r = p_term(r_err, kp);
    const double d_out_r = d_term(r_err, position_mc_prev_err_r, MC_DT, kd);
    position_mc_prev_err_l = l_err;
    position_mc_prev_err_r = r_err;
    
    const double l_out = p_out_l;// + d_out_l;
    const double r_out = p_out_r;// + d_out_r;
    
    // Adjust motor duty cycles
    l_duty = -l_out;
    r_duty = -r_out;
    
    if(l_duty > L_DUTY_BOUND)            l_duty =  L_DUTY_BOUND;
    else if(fabs(l_duty) > L_DUTY_BOUND) l_duty = -L_DUTY_BOUND;
    
    if(r_duty > R_DUTY_BOUND)            r_duty =  R_DUTY_BOUND;
    else if(fabs(r_duty) > R_DUTY_BOUND) r_duty = -R_DUTY_BOUND;
    
    set_pwm_duty_l(l_duty);
    set_pwm_duty_r(r_duty);
}


void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; // Clear T2 interrupt flag.
    
    // Update global state variables
    signed long long l_pos_curr = get_qei_l_pos();
    signed long long r_pos_curr = get_qei_r_pos();
    double l_vel_curr = ((double) (l_pos_curr - l_pos)) / (double) MC_DT;
    double r_vel_curr = ((double) (r_pos_curr - r_pos)) / (double) MC_DT;
    double l_acc_curr = (l_vel_curr - l_vel) / (double) MC_DT;
    double r_acc_curr = (r_vel_curr - r_vel) / (double) MC_DT;
    
    l_pos = l_pos_curr;
    r_pos = r_pos_curr;
    l_vel = l_vel_curr;
    r_vel = r_vel_curr;
    l_acc = l_acc_curr;
    r_acc = r_acc_curr;
    
    scan_ll = get_scan_ll();
    scan_lf = get_scan_lf();
    scan_rr = get_scan_rr();
    scan_rf = get_scan_rf();
    
    // Call current MC function
    (*motor_control)();
}