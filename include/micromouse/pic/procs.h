/**
 * File:
 *     procs.h
 *
 * Description:
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */    

#ifndef MICROMOUSE_PIC_PROCS_H_
#define MICROMOUSE_PIC_PROCS_H_

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum {
    LEFT_HUG,
    RIGHT_HUG,
    UP_N_DOWN
} operation_t;


// Interface functions

operation_t screen_select();

void startup_proc();

void left_hug_proc();

void right_hug_proc();

void up_n_down_proc();
    

#ifdef	__cplusplus
}
#endif

#endif	// MICROMOUSE_PIC_PROCS_H_
