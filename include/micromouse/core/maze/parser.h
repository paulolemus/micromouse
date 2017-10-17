/*
 * File     : parser.h
 * Author   : Paulo Lemus
 * Created  : 9/21/2017
 */

#ifndef MICROMOUSE_CORE_MAZE_PARSER_H_
#define MICROMOUSE_CORE_MAZE_PARSER_H_

#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>

/**
 * @brief Populate a maze with the contents of a file.
 *
 * @param maze The 2D array representing a maze.
 * @param fname The name of the file to parse in.
 * @return 1 if success, 0 if failure.
 */
unsigned int parse_maze(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT], 
    const char* fname
);


#endif // MICROMOUSE_CORE_MAZE_PARSER_H_
