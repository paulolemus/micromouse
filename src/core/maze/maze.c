/*
 * File     : maze.c
 * Author   : Paulo Lemus
 * Created  : 8/28/2017
 */

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

/*
 * Calculate the position in the array that corresponds to (x, y),
 * then use bitwise OR to turn on the single bit without affecting 
 * any other bits.
 */
void setBitOn(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    unsigned int x, 
    unsigned int y, 
    unsigned char mask
) {
    maze[x][y] |= mask;
}

/*
 * Calcuate array index that corresponds to (x, y),
 * then use negated bitwise AND to turn off the single bit.
 */
void setBitOff(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    unsigned int x, 
    unsigned int y, 
    unsigned char mask
) {
    maze[x][y] &= ~mask;
}

/*
 * Calculate index from (x, y), then use bitwise AND to
 * check if value is set or not.
 */
unsigned int isBitSet(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    unsigned int x, 
    unsigned int y, 
    unsigned char mask
) {
    if(maze[x][y] & mask) return 1;
    else                  return 0;
}

/*
 * Calculate array index of (x, y), then return copy of the BLOCK.
 */
unsigned char getBlock(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    unsigned int x, 
    unsigned int y
) {
    return maze[x][y];
}

