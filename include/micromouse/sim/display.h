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
void init_display(
    const unsigned int width,
    const unsigned int height
);

/**
 * @brief Clear all text and colors on NCURSES screen.
 */
void clear_display();

/**
 * @brief Draw all changes to screen. Must be called to see changes.
 */
void render();

/**
 * @brief restore the terminal to default values.
 *        Required before exiting or input and appearence may be wrong.
 */
void finish_display();

/**
 * @brief Put a mouse on the screen.
 * @param dir Direction the mouse is facing.
 * @param x X coordinate of the mouse.
 * @param y Y coordinate of the mouse.
 */
void put_mouse(
    const unsigned int dir,
    const unsigned int x,
    const unsigned int y
);

/**
 * @brief Draw all the walls for a completed maze in a darker color
 * @param WIDTH Width to consider of maze.
 * @param HEIGHT height to consider of maze.
 * @param maze A representation of the maze.
 */
void put_hidden_walls(
    const unsigned int WIDTH,
    const unsigned int HEIGHT,
    BLOCK maze[WIDTH][HEIGHT]
);

/**
 * @brief Place a wall in the desired block.
 * @param maze structure that represents a maze. 
 */
void put_visible_walls(
    const unsigned int WIDTH,
    const unsigned int HEIGHT,
    BLOCK maze[WIDTH][HEIGHT]
);

/**
 * @brief Put a path in the maze.
 * TODO: Figure out path
 */
void put_path();


#endif // MICROMOUSE_SIM_DISPLAY_H_
