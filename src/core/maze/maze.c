/*
 * File     : maze.c
 * Author   : Paulo Lemus
 * Created  : 8/28/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>


unsigned set_maze_dimensions(
    Maze* maze,
    const unsigned width,
    const unsigned height
) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;

    if(width > MAX_WIDTH || height > MAX_HEIGHT) {
        return FAILURE;
    } else {
        maze->width = width;
        maze->height = height;
        return SUCCESS;
    }
}

/**
 * @brief Clear all the bits in a maze to 0.
 * @param maze A pointer to the maze.
 */
void clear_maze(Maze* maze) {
    for(unsigned i = 0; i < MAX_WIDTH; ++i) {
        for(unsigned j = 0; j < MAX_HEIGHT; ++j) {
            maze->maze[i][j] = 0;
        }
    }
}

void box_maze(
    Maze* maze
) {
    // Draw North and South walls
    for(unsigned i = 0; i < maze->width; ++i) {
        setBitOn(maze, i, 0, SOUTH_WALL); 
        setBitOn(maze, i, maze->height - 1, NORTH_WALL);
    }
    
    // Draw West and East walls
    for(unsigned j = 0; j < maze->height; ++j) {
        setBitOn(maze, 0, j, WEST_WALL);
        setBitOn(maze, maze->width - 1, j, EAST_WALL);
    }
}

/*
 * Calculate the position in the array that corresponds to (x, y),
 * then use bitwise OR to turn on the single bit without affecting 
 * any other bits.
 */
void setBitOn(
    Maze* maze,
    const unsigned x, 
    const unsigned y, 
    const unsigned char mask
) {
    maze->maze[x][y] |= mask;
}

/*
 * Calcuate array index that corresponds to (x, y),
 * then use negated bitwise AND to turn off the single bit.
 */
void setBitOff(
    Maze* maze,
    const unsigned x, 
    const unsigned y, 
    const unsigned char mask
) {
    maze->maze[x][y] &= ~mask;
}

/*
 * Calculate index from (x, y), then use bitwise AND to
 * check if value is set or not.
 */
unsigned isBitSet(
    Maze* maze,
    const unsigned x, 
    const unsigned y, 
    const unsigned char mask
) {
    if(maze->maze[x][y] & mask) return 1;
    else                        return 0;
}

/*
 * Calculate array index of (x, y), then return copy of the BLOCK.
 */
unsigned char getBlock(
    Maze* maze,
    const unsigned x, 
    const unsigned y
) {
    return maze->maze[x][y];
}

