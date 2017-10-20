/*
 * File  : display.h
 * Author: Paulo Lemus
 */

/*
 * Display takes care of all rendering to screen.
 */
#ifndef MICROMOUSE_SIM_DISPLAY_H_
#define MICROMOUSE_SIM_DISPLAY_H_

#include <micromouse/core/maze/maze.h>

// Used for mouse facing
#define NORTH 0
#define EAST  1
#define WEST  2
#define SOUTH 3

/**
 * @brief Initilize display environment (NCURSES), clear screen.
 *        This does not render anything, simply sets up environment,
 *        and must be called once at start of simulation.
 * @param width used to set internal width state.
 * @param height used to set internal height state.
 */
void init_display(unsigned int width, unsigned int height);

/**
 * @brief Draw all the walls for a completed maze in a darker color
 * @param 
 */
void put_hidden_walls();

/**
 * @brief Place a wall in the desired block.
 * @param x X coordinate of block.
 * @param y Y coordinate of block.
 * @param block contains bits that tell if a wall exists.
 */
void put_walls(unsigned int x, unsigned int y, BLOCK block);

/**
 * @brief Put a path in the maze.
 *
 */
void put_path();

/**
 * @brief Draw all changes to screen. Must be called to see changes.
 */
void render();

#endif // MICROMOUSE_SIM_DISPLAY_H_
