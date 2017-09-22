/*
 * File     : maze.c
 * Author   : Paulo Lemus
 * Created  : 8/28/2017
 */

#include <stdlib.h>
#include <micromouse/core/maze/maze.h>

/*
 * Allocate memory for a new maze structure.
 * Initialize the unsigned char array so all uchars are zeroed.
 * Initialize the width and height values of the struct.
 */
struct Maze* newMaze(unsigned int width, unsigned int height) {
    struct Maze* maze = (struct Maze*) malloc(sizeof(struct Maze));
    unsigned char* mat = 
        (unsigned char*) calloc(width * height, sizeof(unsigned char));

    maze->mat = mat;
    maze->width = width;
    maze->height = height;
    return maze;
}

/*
 * Free the memory of both the maze struct and of the unsigned
 * char array inside the struct.
 */
void deleteMaze(struct Maze* maze) {
    if(maze) {
        if(maze->mat) {
            free(maze->mat);
        }
        free(maze);
    }
}

/*
 * Calculate the position in the array that corresponds to (x, y),
 * then use bitwise OR to turn on the single bit without affecting 
 * any other bits.
 */
void setBitOn(struct Maze* maze, unsigned int x, unsigned int y, unsigned char mask) {
    maze->mat[maze->width * y + x] |= mask;
}

/*
 * Calcuate array index that corresponds to (x, y),
 * then use negated bitwise AND to turn off the single bit.
 */
void setBitOff(struct Maze* maze, unsigned int x, unsigned int y, unsigned char mask) {
    maze->mat[maze->width * y + x] &= ~mask;
}

/*
 * Calculate index from (x, y), then use bitwise AND to
 * check if value is set or not.
 */
unsigned int isBitSet(struct Maze* maze, unsigned int x, unsigned int y, unsigned char mask) {
    if(maze->mat[maze->width * y + x] & mask) return 1;
    else                                      return 0;
}

/*
 * Calculate array index of (x, y), then return copy of the block.
 */
unsigned char getBlock(struct Maze* maze, unsigned int x, unsigned int y) {
    return maze->mat[maze->width * y + x];
}

