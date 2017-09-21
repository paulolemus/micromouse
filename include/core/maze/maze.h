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

#ifndef MICROMOUSE_CORE_MAZE_H_
#define MICROMOUSE_CORE_MAZE_H_

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
#define M_VISITED    16
#define M_UNCERTAIN  32
#define M_NORTH_WALL_IDX 0
#define M_SOUTH_WALL_IDX 1
#define M_EAST_WALL_IDX  2
#define M_WEST_WALL_IDX  3
#define M_VISITED_IDX    4
#define M_UNCERTAIN_IDX  5

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
    unsigned char* mat;
    unsigned int width;
    unsigned int height;
};

/**
 * @brief Constructor function that builds and initialized 
 *        a maze structure.
 *
 * @param width A positive int representing width.
 * @param height A positive int representing height.
 * @return A pointer to the newly created maze struct.
 */
struct Maze* newMaze(unsigned int width, unsigned int height);

/**
 * @brief Deconstructor for a maze structure.
 *        It deletes the maze as well as the inner char array.
 *        Use this when you are done with a maze.
 *
 * @param maze A pointer to the maze to be deleted.
 */
void deleteMaze(struct Maze* maze);

/**
 * @brief Turn on a single bit in the block found at the coordinate (x, y).
 *        Note that (0, 0) is the "bottom-left" corner of the maze, and 
 *        (xmax, ymax) is the "top-right" corner.
 *
 * @param maze A pointer to the maze struct to add the bit to.
 * @param x The x coordinate of the block.
 * @param y The y coordinate of the block.
 * @param mask A mask representing the bit to turn on in the block.
 */
void setBitOn(struct Maze* maze, unsigned int x, unsigned int y, unsigned char mask);

/**
 * @brief Turn off a single bit in the block found at (x, y).
 *        Note (0, 0) is "bottom-left" corner, while (xmax, ymax)
 *        is the "top-right" corner.
 *
 * @param maze A pointer to the maze struct to turn off the bit from.
 * @param x The x coordinate in the maze of the block.
 * @param y The y coordinate in the maze of the block.
 * @param mask A bitmask representing the bit to turn off.
 */
void setBitOff(struct Maze* maze, unsigned int x, unsigned int y, unsigned char mask);

/**
 * @brief Check if the given bit is set or not.
 *
 * @param maze A pointer to the maze struct.
 * @param x The x coordinate in the maze of the block.
 * @param y The y coordinate in the maze of the block.
 * @param mask A bitmask representing the bit to check.
 * @return 1 if bit is on, 0 if bit is off.
 */
unsigned int isBitSet(struct Maze* maze, unsigned int x, unsigned int y, unsigned char mask);

/**
 * @brief Get a copy of the "block" at the (x, y) coordinate of the maze.
 *
 * @param maze A pointer to our maze.
 * @param x The x coordinate of the block.
 * @param y The y coordinate of the block.
 * @return A copy of the block.
 */
unsigned char getBlock(struct Maze* maze, unsigned int x, unsigned int y);

#endif // MICROMOUSE_UNICORN_MAZE_H_
