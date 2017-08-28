/**
 * File     : maze.h
 * Created  : 8/27/2017
 * Modified : 8/27/2017
 *
 * Header file for the maze struct.
 * The maze struct models a maze (duh).
 *
 * Several functions are provided as a way to obtain, modify,
 * get info from, and delete a maze.
 */

#ifndef MICROMOUSE_UNICORN_MAZE_H_
#define MICROMOUSE_UNICORN_MAZE_H_

/**
 * Char bit masks
 * 
 * These definitions define what each bit in a char represents 
 * for one block of the maze. The maze is a matrix of chars,
 * and each char has 8 bits, meaning 8 possible fields of info
 * per block.
 */
#define M_NORTH_WALL 1
#define M_SOUTH_WALL 2
#define M_EAST_WALL  4
#define M_WEST_WALL  8
#define M_NORTH_WALL_IDX 0
#define M_SOUTH_WALL_IDX 1
#define M_EAST_WALL_IDX  2
#define M_WEST_WALL_IDX  3

/**
 * Maze struct that models a maze. Should only be created, modified,
 * and deleted with the below functions.
 * Each index in the matrix represents a block in the maze.
 * The "char" data type was selected because it allows us to be space efficient;
 * the PIC microcontroller this will run on has limited memory.
 * A bit mask for each char for data on the block such as:
 *      * is there a  "north wall"
 *      * is there an "east wall"
 *      * is there a  "west wall"
 *      * is there a  "south wall"
 * assuming that "north" is the direction the mouse starts in.
 * The mouse should always start facing north in the (0, 0) block.
 *
 * Keep in mind that mat is an array representing a matrix.
 * This was done so all blocks exist in contiguous memory.
 */
struct Maze {
    char* mat;
    int width;
    int height;
};

/**
 * Maze creation and destruction functions.
 */
struct Maze  newMaze(int width, int height);
struct Maze* newMazePtr(int width, int height);

void deleteMaze   (struct Maze maze);
void deleteMazePtr(struct Maze* mazeptr);

/**
 * Maze modification functions
 *
 * My convention for maze coordinates:
 * (x, y)
 * (0, 0)     = bottom-left corner
 * (max, max) = top-right corner
 * x increases going right, decreases going left
 * y increases going up, decreases going down
 */
// Set a bit on using bitwise OR (efficient)
void setBlockBitOn(struct Maze maze, int x, int y, int mask);
// Set a bit off using bitwise AND ~ (efficient)
void setBlockBitOff(struct Maze maze, int x, int y, int mask);
// Get a char from maze
char getBlock(struct Maze maze, int x, int y);
// Check if block's bit is set
int isBlockBitSet(struct Maze maze, int x, int y, int mask);

#endif // MICROMOUSE_UNICORN_MAZE_H_
