/*
 * File: controls.h
 * Author: Paulo Lemus
 */

/* functions used for getting input from user in ncurses.
 */

#ifndef MICROMOUSE_SIM_BASE_H_
#define MICROMOUSE_SIM_BASE_H_

#include <micromouse/core/pathplanning/coord.h>
#include <micromouse/core/pathplanning/directions.h>


/**
 * @brief Check if any keys were pressed / if input can be grabbed.
 *        This allows us to get characters from stdin in a 
 *        non-blocking fashion.
 * @return 1 if has input, 0 if there is nothing to get.
 */
int kbhit();

/**
 * @brief used to pause a simulation so that it refreshes at the 
 *        rate of the mouse speed.
 * @param speed the speed as a double for blocks / second.
 */
void sim_sleep(
    const double speed
);

/**
 * @brief move a simulate mouse according to the given direction.
 * @param mouse_pos the current position of the mouse.
 * @param mouse_dir Current absolute facing of the mouse.
 * @param movement The relative motion for the mouse to make.
 */
void move_sim_mouse(
    Coord* mouse_pos,
    Direct* mouse_dir,
    const Relative movement 
);


#endif //MICROMOUSE_SIM_BASE_H_
