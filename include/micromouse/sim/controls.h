/*
 * File: controls.h
 * Author: Paulo Lemus
 */

/* functions used for getting input from user in ncurses.
 */

#ifndef MICROMOUSE_SIM_CONTROLS_H_
#define MICROMOUSE_SIM_CONTROLS_H_

/**
 * @brief Check if any keys were pressed / if input can be grabbed.
 *        This allows us to get characters from stdin in a 
 *        non-blocking fashion.
 * @return 1 if has input, 0 if there is nothing to get.
 */
int kbhit();


#endif //MICROMOUSE_SIM_CONTROLS_H_
