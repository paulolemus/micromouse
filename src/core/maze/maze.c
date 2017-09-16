/**
 * File     : maze.c
 * Created  : 8/28/2017
 * Modified : 8/28/2017
 */

#include <stdlib.h>
#include "core/maze/maze.h"

/**
 * @brief Create a maze strut that contains:
 *      a char array representing the maze and the width and height.
 * @return struct Maze* a pointer to this created maze.
 *      I chose to return a pointer because if I were to pass the maze by value
 *      to every function, it may end up taking too much stackspace on the 
 *      limited memory of the PIC.
 *
 * TODO: Determine if it is better to grab height and width from the 
 *       defined constants so that the char array is in contiguous memory with
 *       the rest of the structure.
 */
struct Maze* newMaze(int width, int height) {
    struct Maze* maze = (struct Maze*) malloc(sizeof(struct Maze));
    char* mat = (char*) calloc(width * height, sizeof(char));

    maze->mat = mat;
    maze->width = width;
    maze->height = height;
    return maze;
}

/**
 * @brief free a dynamically allocated Maze structure
 */
void deleteMaze(struct Maze* maze) {
    if(maze) {
        if(maze->mat) {
            free(maze->mat);
        }
        free(maze);
    }
}

/**
 * @brief Set a flag bit in one of the maze's blocks.
 *        This is accomplished by 'OR'ing the char with the mask value,
 *        which should only be one bit, thus setting the bit to 1 and leaving
 *        the other bits alone.
 *
 * @param maze A pointer to a maze object.
 * @param x The x value of the block, with x going left to right starting at 0
 * @param y The y value of the block, with y going top to bottom starting at 0
 * @param mask A defined value found in maze.h starting with M_ 
 */
void setBitOn(struct Maze* maze, int x, int y, int mask) {
    maze->mat[maze->width * y + x] |= mask;
}

/**
 * @brief Set a flag bit OFF in one of the maze's blocks.
 *        This is accomplished by inverting the bit to set OFF so all bits are
 *        set except the one. It is then 'AND'ed with the char to set the
 *        one bit to 0.
 *
 * @param maze A pointer to a maze object.
 * @param x The x value of the block, with x going left to right starting at 0
 * @param y The y value of the block, with y going top to bottom starting at 0
 * @param mask A defined value found in maze.h starting with M_ 
 */
void setBitOff(struct Maze* maze, int x, int y, int mask) {
    maze->mat[maze->width * y + x] &= ~mask;
}

char getBlock(struct Maze* maze, int x, int y) {
    return maze->mat[maze->width * y + x];
}

int isBitSet(struct Maze* maze, int x, int y, int mask) {
    if(maze->mat[maze->width * y + x] & mask) return 1;
    else                                      return 0;
}
