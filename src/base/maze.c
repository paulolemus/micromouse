/**
 * File     : maze.c
 * Created  : 8/28/2017
 * Modified : 8/28/2017
 */

#include <stdlib.h>
#include "base/maze.h"

/**
 * Create new Maze struct and return it.
 * The matrix is built as an array so all blocks are contiguous.
 * Calloc is used to clear all bits to zero.
 */
struct Maze newMaze(int width, int height) {
    struct Maze maze;
    char* mat = (char*) calloc(width * height, sizeof(char));
    maze.mat    = mat;
    maze.width  = width;
    maze.height = height;
    return maze;
}

/**
 * Same as above, but return a pointer to a maze.
 * TODO: decide if pointer or no pointer is better.
 */
struct Maze* newMazePtr(int width, int height) {
    struct Maze* maze = (struct Maze*) malloc(sizeof(struct Maze));
    char* mat = (char*) calloc(width * height, sizeof(char));

    maze->mat = mat;
    maze->width = width;
    maze->height = height;
    return maze;
}

void deleteMaze(struct Maze maze) {
    if(maze.mat) free(maze.mat);
}

void deleteMazePtr(struct Maze* maze) {
    if(maze) {
        if(maze->mat) {
            free(maze->mat);
        }
        free(maze);
    }
}

void setBlockBitOn(struct Maze maze, int x, int y, int mask) {
    maze.mat[maze.width * y + x] |= mask;
}

void setBlockBitOff(struct Maze maze, int x, int y, int mask) {
    maze.mat[maze.width * y + x] &= ~mask;
}

char getBlock(struct Maze maze, int x, int y) {
    return maze.mat[maze.width * y + x];
}

int isBlockBitSet(struct Maze maze, int x, int y, int mask) {
    if(maze.mat[maze.width * y + x] & mask) return 1;
    else                                    return 0;
}
