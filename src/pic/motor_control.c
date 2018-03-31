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

// Downscale us to ms
#define DS 1000

///
/// Global Internal State Variables
///

// Desired duty cycles
static volatile long double l_duty = 0.0;
static volatile long double r_duty = 0.0;

// QEI variables
static volatile signed long long int l_pos = 0;
static volatile signed long long int r_pos = 0;
static long double l_vel = 0.0;
static long double r_vel = 0.0;
static long double l_acc = 0.0;
static long double r_acc = 0.0;

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
static volatile signed long long int position_mc_target_l;
static volatile signed long long int position_mc_target_r;
static long double position_mc_prev_err_l = 0.0;
static long double position_mc_prev_err_r = 0.0;
void init_position_mc() {
    // Function statics
    position_mc_target_l = l_pos;
    position_mc_target_r = r_pos;
    position_mc_prev_err_l = 0.0;
    position_mc_prev_err_r = 0.0;
    
    // Global statics
    l_duty = 0.0;
    r_duty = 0.0;
}
void position_mc() {
    const long double kp = 0.06;
    const long double kd = 0.02;
    
    // Calculate error in position
    const long double l_err = (long double) (l_pos - position_mc_target_l);
    const long double r_err = (long double) (r_pos - position_mc_target_r);
    
    // Calculate PID outputs
    const long double p_out_l = p_term(l_err, kp);
    const long double d_out_l = d_term(l_err, position_mc_prev_err_l, (long double) MC_DT, kd);
    const long double p_out_r = p_term(r_err, kp);
    const long double d_out_r = d_term(r_err, position_mc_prev_err_r, (long double) MC_DT, kd);
    position_mc_prev_err_l = l_err;
    position_mc_prev_err_r = r_err;
    
    const long double l_out = p_out_l + d_out_l;
    const long double r_out = p_out_r + d_out_r;
    
    // Adjust motor duty cycles
    l_duty = -l_out;
    r_duty = -r_out;
    
    set_pwm_duty_l(l_duty);
    set_pwm_duty_r(r_duty);
}


/**
 * The mouse will drive in a straight line.
 */
static long double straight_l_vel_err;
static long double straight_r_vel_err;
void init_straight_mc() {
    straight_l_vel_err = l_vel;
    straight_r_vel_err = r_vel;
}
void straight_mc() {
    const long double l_vel_sp = 5.0; // Velocity setpoint is 5 ticks/ms
    const long double r_vel_sp = 5.0; // Velocity setpoint is 5 ticks/ms
    const long double kp = 0.33;
    const long double kd = 4.0;
    
    const long double l_vel_err = l_vel_sp - l_vel;
    const long double r_vel_err = r_vel_sp - r_vel;

    const long double p_out_l = p_term(l_vel_err, kp);
    const long double p_out_r = p_term(r_vel_err, kp);
    const long double d_out_l = d_term(l_vel_err, straight_l_vel_err, MC_DT, kd);
    const long double d_out_r = d_term(r_vel_err, straight_r_vel_err, MC_DT, kd);
    straight_l_vel_err = l_vel_err;
    straight_r_vel_err = r_vel_err;

    const long double l_out = p_out_l + d_out_l;
    const long double r_out = p_out_r + d_out_r;

    l_duty += l_out;
    r_duty += r_out;
    
    if(l_duty < 0.0) l_duty = 0;
    if(r_duty < 0.0) r_duty = 0;
    
    set_pwm_duty_l(l_duty);
    set_pwm_duty_r(r_duty);
}


static volatile long double trk_l_sns_err;
static volatile long double trk_r_sns_err;
static volatile long double trk_l_vel_err;
static volatile long double trk_r_vel_err;
void init_track_mc() {
    trk_l_sns_err = 0.0;
    trk_r_sns_err = 0.0;
    trk_l_vel_err = 0.0;
    trk_r_vel_err = 0.0;
}
void track_mc() {
    const long double vel_base = 10.0;
    const long double l_vel_sp = 7.0;
    const long double r_vel_sp = 7.0;
    const unsigned int l_trk_sp = get_close_ll();
    const unsigned int r_trk_sp = get_close_rr();
    
    const long double vel_kp = 22.0;
    const long double vel_kd = 0.1;
    
    const long double l_sns_kp = 0.12;
    const long double l_sns_kd = 0.001;
    const long double r_sns_kp = 0.12;
    const long double r_sns_kd = 0.001;
    
    LED_OFF(LED_L);
    LED_OFF(LED_R);
    
    // Calculate velocity PID
    const long double l_vel_err = l_vel_sp - l_vel;
    const long double r_vel_err = r_vel_sp - r_vel;

    const long double p_vel_out_l = p_term(l_vel_err, vel_kp);
    const long double p_vel_out_r = p_term(r_vel_err, vel_kp);
    const long double d_vel_out_l = d_term(l_vel_err, trk_l_vel_err, MC_DT, vel_kd);
    const long double d_vel_out_r = d_term(r_vel_err, trk_r_vel_err, MC_DT, vel_kd);
    trk_l_vel_err = l_vel_err;
    trk_r_vel_err = r_vel_err;
    
    // Limit acceleration
    const long double acc_kp = 0.0;
    const long double l_acc_out = -p_term(l_acc, acc_kp);
    const long double r_acc_out = -p_term(r_acc, acc_kp);

    const long double l_vel_out = p_vel_out_l + d_vel_out_l + l_acc_out;
    const long double r_vel_out = p_vel_out_r + d_vel_out_r + r_acc_out;
    
    
    signed int l_sns_err = 0;
    signed int r_sns_err = 0;
    signed int sns_out = 0;
    // Calculate sensor push
    if(scan_ll > get_close_ll() - 400) {
        // Using Left sensor
        LED_ON(LED_L);
        
        l_sns_err = scan_ll - l_trk_sp;
        
        const long double p_sns = p_term(l_sns_err, l_sns_kp);
        const long double d_sns = d_term(l_sns_err, trk_l_vel_err, MC_DT, l_sns_kd);
        sns_out = p_sns + d_sns;
        trk_l_sns_err = l_sns_err;
        trk_r_sns_err = scan_rr - r_trk_sp;
        
    } else if(scan_rr > get_close_rr() - 400) {
        // Using right sensor
        LED_ON(LED_R);
        
        r_sns_err = r_trk_sp - scan_rr;
        
        const long double p_sns = p_term(r_sns_err, r_sns_kp);
        const long double d_sns = d_term(r_sns_err, trk_r_vel_err, MC_DT, r_sns_kd);
        sns_out = p_sns + d_sns;
        trk_r_sns_err = r_sns_err;
        trk_l_sns_err = scan_ll - l_trk_sp;
    }
    
    // Combine terms
    const long double l_out = l_vel_out + sns_out;
    const long double r_out = r_vel_out - sns_out;
    
    l_duty = vel_base + l_out;
    r_duty = vel_base + r_out;
    
    if(l_duty < 0.0) l_duty = 0;
    if(r_duty < 0.0) r_duty = 0;
    
    set_pwm_duty_l(l_duty);
    set_pwm_duty_r(r_duty);
}

static volatile signed long long int left_mc_target_l;
static volatile signed long long int left_mc_target_r;
static long double left_mc_prev_err_l;
static long double left_mc_prev_err_r;
void init_left_mc() {
    // Function statics
    left_mc_target_l = l_pos - 1350;
    left_mc_target_r = r_pos + 1350;
    left_mc_prev_err_l = 0.0;
    left_mc_prev_err_r = 0.0;
    
    // Global statics
    l_duty = 0.0;
    r_duty = 0.0;
}
void left_mc() {
    const long double kp = 0.045;
    const long double kd = 0.1;
    
    // Calculate error in position
    const long double l_err = (long double) (l_pos - left_mc_target_l);
    const long double r_err = (long double) (r_pos - left_mc_target_r);
    
    // Calculate PID outputs
    const long double p_out_l = p_term(l_err, kp);
    const long double d_out_l = d_term(l_err, left_mc_prev_err_l, (long double) MC_DT, kd);
    const long double p_out_r = p_term(r_err, kp);
    const long double d_out_r = d_term(r_err, left_mc_prev_err_r, (long double) MC_DT, kd);
    left_mc_prev_err_l = l_err;
    left_mc_prev_err_r = r_err;
    
    const long double l_out = p_out_l + d_out_l;
    const long double r_out = p_out_r + d_out_r;
    
    // Adjust motor duty cycles
    l_duty = -l_out;
    r_duty = -r_out;
    
    set_pwm_duty_l(l_duty);
    set_pwm_duty_r(r_duty);
}

static volatile signed long long int right_mc_target_l;
static volatile signed long long int right_mc_target_r;
static long double right_mc_prev_err_l;
static long double right_mc_prev_err_r;
void init_right_mc() {
    // Function statics
    right_mc_target_l = l_pos + 1350;
    right_mc_target_r = r_pos - 1350;
    right_mc_prev_err_l = 0.0;
    right_mc_prev_err_r = 0.0;
    
    // Global statics
    l_duty = 0.0;
    r_duty = 0.0;
}
void right_mc() {
    const long double kp = 0.045;
    const long double kd = 0.1;
    
    // Calculate error in position
    const long double l_err = (long double) (l_pos - right_mc_target_l);
    const long double r_err = (long double) (r_pos - right_mc_target_r);
    
    // Calculate PID outputs
    const long double p_out_l = p_term(l_err, kp);
    const long double d_out_l = d_term(l_err, right_mc_prev_err_l, (long double) MC_DT, kd);
    const long double p_out_r = p_term(r_err, kp);
    const long double d_out_r = d_term(r_err, right_mc_prev_err_r, (long double) MC_DT, kd);
    right_mc_prev_err_l = l_err;
    right_mc_prev_err_r = r_err;
    
    const long double l_out = p_out_l + d_out_l;
    const long double r_out = p_out_r + d_out_r;
    
    // Adjust motor duty cycles
    l_duty = -l_out;
    r_duty = -r_out;
    
    set_pwm_duty_l(l_duty);
    set_pwm_duty_r(r_duty);
}


static volatile signed long long int around_mc_target_l;
static volatile signed long long int around_mc_target_r;
static long double around_mc_prev_err_l;
static long double around_mc_prev_err_r;
void init_around_mc() {
    // Function statics
    around_mc_target_l = l_pos + 2800;
    around_mc_target_r = r_pos - 2800;
    around_mc_prev_err_l = 0.0;
    around_mc_prev_err_r = 0.0;
    
    // Global statics
    l_duty = 0.0;
    r_duty = 0.0;
}
void around_mc() {
    const long double kp = 0.07;
    const long double kd = 0.25;
    
    // Calculate error in position
    const long double l_err = (long double) (l_pos - around_mc_target_l);
    const long double r_err = (long double) (r_pos - around_mc_target_r);
    
    // Calculate PID outputs
    const long double p_out_l = p_term(l_err, kp);
    const long double d_out_l = d_term(l_err, around_mc_prev_err_l, (long double) MC_DT, kd);
    const long double p_out_r = p_term(r_err, kp);
    const long double d_out_r = d_term(r_err, around_mc_prev_err_r, (long double) MC_DT, kd);
    around_mc_prev_err_l = l_err;
    around_mc_prev_err_r = r_err;
    
    const long double l_out = p_out_l + d_out_l;
    const long double r_out = p_out_r + d_out_r;
    
    // Adjust motor duty cycles
    l_duty = -l_out;
    r_duty = -r_out;
    
    set_pwm_duty_l(l_duty);
    set_pwm_duty_r(r_duty);
}


void update_mc_state() {
    // Update global state variables
    signed long long l_pos_curr = get_qei_l_pos();
    signed long long r_pos_curr = get_qei_r_pos();
    double l_vel_curr = ((double) (l_pos_curr - l_pos)) / (double) (MC_DT/DS);
    double r_vel_curr = ((double) (r_pos_curr - r_pos)) / (double) (MC_DT/DS);
    double l_acc_curr = (l_vel_curr - l_vel) / (double) (MC_DT/DS);
    double r_acc_curr = (r_vel_curr - r_vel) / (double) (MC_DT/DS);
    
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
}

static volatile int mc_interrupt = 0;
void wait_mc() {
    mc_interrupt = 0;
    
    while(!mc_interrupt);
}


void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; // Clear T2 interrupt flag.
    
    mc_interrupt = 1;
    signed long long l_pos_curr = get_qei_l_pos();
    signed long long r_pos_curr = get_qei_r_pos();
    double l_vel_curr = ((double) (l_pos_curr - l_pos)) / (double) (MC_DT/DS);
    double r_vel_curr = ((double) (r_pos_curr - r_pos)) / (double) (MC_DT/DS);
    double l_acc_curr = (l_vel_curr - l_vel) / (double) (MC_DT/DS);
    double r_acc_curr = (r_vel_curr - r_vel) / (double) (MC_DT/DS);
    
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
