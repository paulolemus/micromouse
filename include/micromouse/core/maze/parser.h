/*
 * File     : parser.h
 * Author   : Paulo Lemus
 * Created  : 9/21/2017
 */

#ifndef MICROMOUSE_CORE_MAZE_PARSER_H_
#define MICROMOUSE_CORE_MAZE_PARSER_H_

#include <micromouse/core/maze/maze.h>


/**
 * @brief Build a maze struct from information parsed from file.
 *
 * @param filename The name of the file containing the maze data.
 * @return A pointer to a newly allocated maze structure. 
 *         If the maze could not be parsed, returns NULL.
 */
struct Maze* parseMaze(char* filename);


#endif // MICROMOUSE_CORE_MAZE_PARSER_H_
