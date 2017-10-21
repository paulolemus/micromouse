/*
 * File: coord.h
 * Author: Paulo
 */

/*
 * Contains a Coordinate structure that is used for building a path of coords.
 */

#ifndef MICROMOUSE_CORE_PATHPLANNING_COORD_H_
#define MICROMOUSE_CORE_PATHPLANNING_COORD_H_

/**
 * Struct used to keep a single coordinate in a maze.
 * This is useful especially for keeping a path that
 * can easily be iterated.
 */
typedef struct Coord {
    unsigned x;
    unsigned y;
} Coord;

/**
 * @brief Set the x and y values of a Coord.
 * @param x The x value to set.
 * @param y The y value to set.
 */
void set_coord(
    Coord* coord, 
    const unsigned x, 
    const unsigned y
);

#endif // MICROMOUSE_CORE_PATHPLANNING_COORD_H_
