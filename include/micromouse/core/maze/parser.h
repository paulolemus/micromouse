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
 * @param g_width Save the width of maze if less than 16
 * @param g_height Save height of maze if less than 16
 * @param fname The name of the file to parse in.
 * @return 1 if success, 0 if failure.
 */
unsigned parse_maze(
    Maze* maze,
    unsigned* g_width,
    unsigned* g_height,
    const char* fname
);


#endif // MICROMOUSE_CORE_MAZE_PARSER_H_
