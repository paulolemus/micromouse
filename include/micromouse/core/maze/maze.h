/**
 * File     : maze.h
 * Created  : 8/27/2017
 * Modified : 8/27/2017
 *
 * This file contains functions that operate on a maze dat structure.
 * This code is intended to run on a PIC microcontroller, so care
 * must be taken to avoid mallocs. 
 * To create a maze, use the typedef BLOCK, which represents a single BLOCK
 * of the maze.
 *
 */

#ifndef MICROMOUSE_CORE_MAZE_H_
#define MICROMOUSE_CORE_MAZE_H_

#include <micromouse/config.h>

typedef struct Maze {
    unsigned width;
    unsigned height;
    unsigned char maze[MAX_WIDTH][MAX_HEIGHT];
} Maze;

/**
 * Char bit masks
 * 
 * These definitions define what each bit in a char represents 
 * for one BLOCK of the maze. The maze is a matrix of chars,
 * and each char has 8 bits, meaning 8 possible fields of info
 * per BLOCK.
 */
// Walls
#define NORTH_WALL 1
#define SOUTH_WALL 2
#define EAST_WALL  4
#define WEST_WALL  8
// Properties
#define VISITED    16
#define UNCERTAIN  32


/**
 * @brief function to set new width and height of a maze.
 * @param maze A pointer to the maze to modify.
 * @return 1 if success, 0 if failure
 */
unsigned set_maze_dimensions(
    Maze* maze,
    const unsigned width,
    const unsigned height
);

/**
 * @brief Used to initialize each element of a maze to 0.
 *        This is important because we use bitwise operations
 *        to modify the maze.
 * @param maze The representation of the maze.
 */
void clear_maze(
    Maze* maze
);

/**
 * @brief Draw a box around a maze.
 * @param width width to box in
 * @param height height to box in
 * @param maze The maze to add box to
 */
void box_maze(
    Maze* maze
);

/**
 * @brief Sets the wall bit in a maze on, and the corresponding bit
 *        for the block in that wall's direction.
 * @param maze A pointer to the maze to modify.
 * @param x X coordinate of block
 * @param y Y coordinate of block
 * @param wall A wall defined constant.
 */
void set_wall_on(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char wall
);

/**
 * @brief Sets the wall bit in a maze off, and the corresponding bit
 *        for the block in that wall's direction.
 * @param maze A pointer to the maze to modify.
 * @param x X coordinate of block
 * @param y Y coordinate of block
 * @param wall A wall defined constant.
 */
void set_wall_off(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char wall
);

/**
 * @brief check if the wall exists in maze block.
 * @param maze Pointer to maze to check
 * @param x X coordinate of block
 * @param y Y coordinate of block
 * @param wall Defined constant representing wall
 */
unsigned has_wall(
    const Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char wall
);

/**
 * @brief Set a property for a maze block.
 * @param maze Pointer to maze
 * @param x X coordinate
 * @param y Y coordinate
 * @param property A defined constant found in maze.h
 */
void set_property_on(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char property
);

/**
 * @brief Set a property for a maze block off.
 * @param maze Pointer to maze
 * @param x X coordinate
 * @param y Y coordinate
 * @param property A defined constant found in maze.h
 */
void set_property_off(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char property
);

/**
 * @brief Set a property for a maze block.
 * @param maze Pointer to maze
 * @param x X coordinate
 * @param y Y coordinate
 * @param property A defined constant found in maze.h
 */
unsigned has_property(
    const Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char property
);

#endif // MICROMOUSE_UNICORN_MAZE_H_
