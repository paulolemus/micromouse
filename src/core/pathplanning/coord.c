/*
 * File: coord.c
 * Author: Paulo Lemus
 */

#include <micromouse/core/pathplanning/coord.h>

void set_coord(
    Coord* coord,
    const unsigned x,
    const unsigned y
) {
    coord->x = x;
    coord->y = y;
}
