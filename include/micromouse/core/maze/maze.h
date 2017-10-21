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
#define NORTH_WALL 1
#define SOUTH_WALL 2
#define EAST_WALL  4
#define WEST_WALL  8
#define VISITED    16
#define UNCERTAIN  32
#define NORTH_WALL_IDX 0
#define SOUTH_WALL_IDX 1
#define EAST_WALL_IDX  2
#define WEST_WALL_IDX  3
#define VISITED_IDX    4
#define UNCERTAIN_IDX  5

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
 * @brief Turn on a single bit in the BLOCK found at the coordinate (x, y).
 *        Note that (0, 0) is the "bottom-left" corner of the maze, and 
 *        (xmax, ymax) is the "top-right" corner.
 *
 * @param maze A pointer to the maze to add the bit to.
 * @param x The x coordinate of the BLOCK.
 * @param y The y coordinate of the BLOCK.
 * @param mask A mask representing the bit to turn on in the BLOCK.
 */
void setBitOn(
    Maze* maze,
    const unsigned x, 
    const unsigned y, 
    const unsigned char mask
);

/**
 * @brief Turn off a single bit in the BLOCK found at (x, y).
 *        Note (0, 0) is "bottom-left" corner, while (xmax, ymax)
 *        is the "top-right" corner.
 *
 * @param maze A pointer to the maze to turn off the bit from.
 * @param x The x coordinate in the maze of the BLOCK.
 * @param y The y coordinate in the maze of the BLOCK.
 * @param mask A bitmask representing the bit to turn off.
 */
void setBitOff(
    Maze* maze,
    const unsigned x, 
    const unsigned y, 
    const unsigned char mask
);

/**
 * @brief Check if the given bit is set or not.
 *
 * @param maze A pointer to the maze.
 * @param x The x coordinate in the maze of the BLOCK.
 * @param y The y coordinate in the maze of the BLOCK.
 * @param mask A bitmask representing the bit to check.
 * @return 1 if bit is on, 0 if bit is off.
 */
unsigned isBitSet(
    Maze* maze,
    const unsigned x, 
    const unsigned y, 
    const unsigned char mask
);

/**
 * @brief Get a copy of the "BLOCK" at the (x, y) coordinate of the maze.
 *
 * @param maze A pointer to our maze.
 * @param x The x coordinate of the BLOCK.
 * @param y The y coordinate of the BLOCK.
 * @return A copy of the BLOCK.
 */
unsigned char getBlock(
    Maze* maze,
    const unsigned x, 
    const unsigned y
);

#endif // MICROMOUSE_UNICORN_MAZE_H_
