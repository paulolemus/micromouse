/*
 * File: path.h
 * Author: Paulo Lemus
 */

/*
 * Path struct used for representing the path from mouse original location
 * to goal. 
 */
#ifndef MICROMOUSE_CORE_PATHPLANNING_PATH_H_
#define MICROMOUSE_CORE_PATHPLANNING_PATH_H_

#include <micromouse/config.h>
#include <micromouse/core/pathplanning/coord.h>


/**
 * @brief Path used to keep a list of coordinates describing a list
 * from one point to another in the maze.
 * Note that the 0th index in the path is the current location of the mouse,
 * and the end index contains the end coordinates of the path.
 *
 * @field next Index of the next coordinate in the path.
 * @field end Index of the last valid coordinate in the path.
 * @field coords The array containing all the coordinates in the path.
 */
typedef struct Path {
    unsigned curr;
    unsigned end;
    Coord coords[PATH_SIZE];
} Path;


/**
 * @brief Clear everything in the path struct to a default state.
 * @param path The path to clear
 */
void clear_path(Path* path);

/**
 * @brief Get the next coordinate in the path, assuming we are
 *        on a coordinate in the path.
 * @param path A pointer to the path to get next from.
 * @return a Coord containing next coordinates to move to.
 */
Coord get_next_coord(const Path* path);

/**
 * @brief Move the path up, as if we moved along it.
 * @param path pointer to path to modify.
 * @return 1 if success, 0 if failure.
 */
unsigned shift_path_up(Path* path);




#endif // MICROMOUSE_CORE_PATHPLANNING_PATH_H_

