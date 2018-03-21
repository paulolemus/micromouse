/**
 * File: 
 *     path.h
 * 
 * Description:
 *     Structure used for representing a path in the maze.
 *     Includes interface for working with Path objects.
 * 
 * Notes:
 *     The max number of cells a path can hold is defined in micromouse
 *     config file.
 *     The zeroth item in a path is the current path, and the last item
 *     is the goal node.
 * 
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_CORE_PATH_H_
#define MICROMOUSE_CORE_PATH_H_ 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "micromouse/config.h"
#include "micromouse/core/maze.h"

    
/**
 * @brief Path used to keep a list of coordinates describing a list
 *        from one point in a maze to another point.
 *        Note that the 0th index is the starting node of the maze.
 *        Node that the endth index is the ending node of the maze.
 *
 * @field curr Index of the current location in the maze.
 * @field end Index of the ending location in the maze.
 * @field coords The array of coordinates. It has a max size of PATH_SIZE
 */
typedef struct Path {
    size_t curr;
    size_t end;
    Coord coords[PATH_SIZE];
} Path;


/**
 * @brief Clear the path to an intial default state.
 *        It initializes curr and end to 0.
 *        It clears all coordinates in coords to 0, 0.
 * @param path The path struct to initialize.
 */
void init_path(
    Path* path
);


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_CORE_MAZE_H_
