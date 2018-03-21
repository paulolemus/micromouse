/**
 * File:
 *     path.c
 *
 * Description:
 *     Implementation for Path structure interface.
 * 
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */


#include "micromouse/config.h"
#include "micromouse/core/path.h"


void init_path(
    Path* path
) {
    unsigned i;
    path->curr = 0;
    path->end = 0;

    for(i = 0; i < PATH_SIZE; ++i) {
        path->coords[i].x = 0;
        path->coords[i].y = 0;
    }
}
