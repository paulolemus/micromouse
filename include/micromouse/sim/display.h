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
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/pathplanning/directions.h>


/**
 * @brief Initilize display environment (NCURSES), clear screen.
 *        This does not render anything, simply sets up environment,
 *        and must be called once at start of simulation.
 * @param width used to set internal width state.
 * @param height used to set internal height state.
 */
void init_display();

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
    const Maze* maze,
    const Direct direction,
    const unsigned x,
    const unsigned y
);

/**
 * @brief draw all the posts for the maze.
 * @param maze Used only for width and height.
 */
void put_posts(
    const Maze* maze
);

/**
 * @brief Draw all the walls for a completed maze in a darker color
 * @param maze A representation of the maze.
 */
void put_hidden_walls(
    const Maze* maze
);

/**
 * @brief Place a wall in the desired block.
 * @param maze structure that represents a maze. 
 */
void put_visible_walls(
    const Maze* maze
);

/**
 * @brief Put a path in the maze.
 */
void put_path(
    const Maze* maze,
    const Path* path    
);


#endif // MICROMOUSE_SIM_DISPLAY_H_
