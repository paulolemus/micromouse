/**
 * File: 
 *     maze.h
 * 
 * Description:
 *     Interface for interacting with a the data model for a maze, 
 *     the Maze structure.
 * 
 * Notes:
 *     There is no make_maze function because dynamic allocation is not desired
 *     for our MCU. Instead, create a maze on the stack and interact with it 
 *     using these functions.
 * 
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_CORE_MAZE_H_
#define MICROMOUSE_CORE_MAZE_H_ 

#ifdef __cplusplus
extern "C" {
#endif

#include "micromouse/config.h"


// Scalar type used to represent a cell in the maze.
typedef unsigned char cell_t;

// Primary Maze data structure.
typedef struct Maze {
    unsigned width;
    unsigned height;
    cell_t maze[MAX_WIDTH][MAX_HEIGHT];
} Maze;

// Secondary type used for representing a coordinate in the maze.
typedef struct Coord {
    unsigned x;
    unsigned y;
} Coord;


/**
 * cell_t bit masks.
 *
 * These define what each bit in a cell_t represents.
 * The maze is a matrix of cell_t, and each bit in a cell_t describes a cell.
 */
// Walls
#define WALL_NORTH 1
#define WALL_SOUTH 2
#define WALL_EAST  4
#define WALL_WEST  8


// Maze interface functions

/**
 * @brief Initialize a maze to a default state.
 *        This clears every bit in the maze to 0 and ensures the provided
 *        width and height values are within bounds.
 *        Use before interacting with maze through other functions.
 * @param maze The maze struct.
 * @param width Width of maze, must be smaller than MAX_WIDTH.
 * @param height Height of maze, must be smaller than MAX_HEIGHT.
 * @return 1 on success, 0 on failure.
 */
unsigned init_maze(
    Maze* maze,
    const unsigned width,
    const unsigned height
);

/**
 * @brief Draw walls around the border of the maze.
 * @param maze The maze struct.
 */
void box_maze(
    Maze* maze
);

/**
 * @brief Sets the mask's field bit to a 1 in the cell (x, y).
 * @param maze The maze struct to modify.
 * @param x X coordinate of cell in maze.
 * @param y Y coordinate of cell in maze.
 * @param mask The bit mask to set in the maze.
 */
void set_field_on(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const cell_t mask
);

/**
 * @brief Sets the mask's field bit to a 0 in the cell (x, y).
 * @param maze The maze struct to modify.
 * @param x X coordinate of cell in maze.
 * @param y Y coordinate of cell in maze.
 * @param mask The bit mask to set in the maze.
 */
void set_field_off(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const cell_t mask
);

/**
 * @brief Checks if the given mask bit was set in the given maze's cell.
 * @param maze The maze struct to modify.
 * @param x X coordinate of cell in maze.
 * @param y Y coordinate of cell in maze.
 * @param mask The bit mask to set in the maze.
 * @return 1 if it was set, 0 otherwise.
 */
unsigned has_field(
    const Maze* maze,
    const unsigned x,
    const unsigned y,
    const cell_t mask
); 


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_CORE_MAZE_H_
