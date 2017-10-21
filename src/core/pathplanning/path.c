/*
 * File: path.c
 * Author: Paulo Lemus
 */

#include <micromouse/config.h>
#include <micromouse/core/pathplanning/path.h>


void clear_path(Path* path) {
    path->next = 0;
    path->end  = 0;
    for(unsigned i = 0; i < PATH_SIZE; ++i) {
        path->coords[i].x = 0;
        path->coords[i].y = 0;
    }
}

Coord get_next_coord(const Path* path) {
    return path->coords[path->next];
}

unsigned shift_path_up(Path* path) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;
    if(path->next == 0 || path->next >= path->end) {
        return FAILURE;
    } else {
        path->next++;
        return SUCCESS;
    }
}

