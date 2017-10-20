/*
 * File     : maze.c
 * Author   : Paulo Lemus
 * Created  : 8/28/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <micromouse/core/maze/maze.h>

/**
 * @brief Clear all the bits in a maze to 0.
 * @param maze A pointer to the maze.
 */
void clear_maze(BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT]) {
    for(unsigned int i = 0; i < MAZE_WIDTH; ++i) {
        for(unsigned int j = 0; j < MAZE_HEIGHT; ++j) {
            maze[i][j] = 0;
        }
    }
}

unsigned int box_maze(
    const unsigned int width,
    const unsigned int height,
    BLOCK maze[width][height]
) {
    const unsigned int SUCCESS = 1;
    const unsigned int FAILURE = 0;
    // Error check
    if(width > MAZE_WIDTH || height > MAZE_HEIGHT ||
       width < 1 || height < 1) {
        fprintf(stderr, "Error: box_maze out of bounds\n");
        return FAILURE;
    }
    // Draw North and South walls
    for(unsigned int i = 0; i < width; ++i) {
        setBitOn(maze, i, 0, SOUTH_WALL); 
        setBitOn(maze, i, height - 1, NORTH_WALL);
    }
    
    // Draw West and East walls
    for(unsigned int j = 0; j < height; ++j) {
        setBitOn(maze, 0, j, WEST_WALL);
        setBitOn(maze, width - 1, j, EAST_WALL);
    }
    return SUCCESS;
}

/*
 * Calculate the position in the array that corresponds to (x, y),
 * then use bitwise OR to turn on the single bit without affecting 
 * any other bits.
 */
void setBitOn(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    const unsigned int x, 
    const unsigned int y, 
    const unsigned char mask
) {
    maze[x][y] |= mask;
}

/*
 * Calcuate array index that corresponds to (x, y),
 * then use negated bitwise AND to turn off the single bit.
 */
void setBitOff(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    const unsigned int x, 
    const unsigned int y, 
    const unsigned char mask
) {
    maze[x][y] &= ~mask;
}

/*
 * Calculate index from (x, y), then use bitwise AND to
 * check if value is set or not.
 */
unsigned int isBitSet(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    const unsigned int x, 
    const unsigned int y, 
    const unsigned char mask
) {
    if(maze[x][y] & mask) return 1;
    else                  return 0;
}

/*
 * Calculate array index of (x, y), then return copy of the BLOCK.
 */
BLOCK getBlock(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    const unsigned int x, 
    const unsigned int y
) {
    return maze[x][y];
}

