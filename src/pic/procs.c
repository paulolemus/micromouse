/**
 * File:
 *     procs.c
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
#include <stdbool.h>

#include "micromouse/config.h"
#include "micromouse/pic/procs.h"
#include "micromouse/pic/motor_control.h"
#include "micromouse/pic/adc.h"
#include "micromouse/pic/utils.h"

#include "micromouse/pic/components/led.h"


operation_t screen_select() {
    return UP_N_DOWN;
}


void startup_proc() {

    // Wait for finger
    while(get_scan_rf() < 1200 && get_scan_rr() < 1200) {
        wait_ms(100);
    }

    // Mini lightshow
    wait_ms(250);
    LED_ON(LED_L);
    LED_ON(LED_R);
    wait_ms(250);
    LED_OFF(LED_L);
    LED_OFF(LED_R);
    wait_ms(250);
    LED_ON(LED_L);
    LED_ON(LED_R);
    wait_ms(250);
    LED_OFF(LED_L);
    LED_OFF(LED_R);
    wait_ms(250);
    update_mc_state();
}

// Calibrate maneuver delays.
#define CENTER_MS 400
#define POS_MS 320
#define TURN_MS 700
#define AROUND_MS 1020

// Sensor offsets
#define RR_ADJ 10
#define LL_ADJ 10

void left_hug_proc() {

    init_track_mc();
    set_motor_control_function(&track_mc);
    update_mc_state();
    enable_motor_control();

    unsigned int left_open = 0;
    unsigned int front_open = 0;

    /*
     * 1. Front open and left closed.
     * 2. front closed and left closed.
     * 3. Front closed and left open.
     */
    while(true) {
        
        // Poll sensors
        if(get_scan_ll() < get_close_ll() + LL_ADJ) {
            left_open = 1;
        } else {
            left_open = 0;
        }

        if(get_scan_lf() < get_close_lf() && get_scan_rf() < get_close_rf()) {
            front_open = 1;
        } else {
            front_open = 0;
        }

        // Repoll 3 times to ensure it wasn't a ghost value
        if(left_open || !front_open) {
            
            wait_ms(2);
            if(get_scan_ll() < get_close_ll() + LL_ADJ) {
                left_open = 1;
            } else {
                left_open = 0;
            }

            if(get_scan_lf() < get_close_lf() && get_scan_rf() < get_close_rf()) {
                front_open = 1;
            } else {
                front_open = 0;
            }
        }


        if(!front_open) {
            // Stop
            init_position_mc();
            set_motor_control_function(&position_mc);
            wait_ms(POS_MS);
            
            // Repoll one more time
            if(get_scan_ll() < get_close_ll() - LL_ADJ) left_open |= 1;
            else                                        left_open |= 0;
            
            if(left_open) {
                // Turn left
                init_left_mc();
                set_motor_control_function(&left_mc);
                wait_ms(TURN_MS);
                
                // Continue driving forward
                init_track_mc();
                set_motor_control_function(&track_mc);
                wait_ms(CENTER_MS / 2);
            } else {
                // Turn right
                init_right_mc();
                set_motor_control_function(&right_mc);
                wait_ms(TURN_MS);
                
                // Continue driving forward
                init_track_mc();
                set_motor_control_function(&track_mc);
            }
            
            
        } else if(left_open == 1) {
            
            // Drive to center of block
            wait_ms(CENTER_MS);
            
            
            // Stop in middle of block
            init_position_mc();
            set_motor_control_function(&position_mc);
            wait_ms(POS_MS);
            
            // Turn left
            init_left_mc();
            set_motor_control_function(&left_mc);
            wait_ms(TURN_MS);
            
            // Continue driving forward
            init_track_mc();
            set_motor_control_function(&track_mc);
            
            // Clear the edge
            wait_ms(CENTER_MS / 1.8);
        }
    }
}

void right_hug_proc() {

}

void up_n_down_proc() {

    update_mc_state();
    init_track_mc();
    set_motor_control_function(&track_mc);
    enable_motor_control();

    while(true) {
        if(get_scan_rf() > get_close_rf() && get_scan_lf() > get_close_lf()) {
            // Stop in place.
            
            init_position_mc();
            set_motor_control_function(&position_mc);
            wait_ms(POS_MS);

            // Turn around
            init_around_mc();
            set_motor_control_function(&around_mc);
            wait_ms(AROUND_MS);

            // Continue driving
            init_track_mc();
            set_motor_control_function(&track_mc);
        }
    }
}
