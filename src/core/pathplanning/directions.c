/*
 * File: directions.c
 * Author: Paulo Lemus
 */

#include <micromouse/config.h>
#include <micromouse/core/pathplanning/directions.h>


void clear_directions(Directions* directions) {
    directions->curr = 0;
    directions->end  = 0;
    for(unsigned i = 0; i < DIRECTIONS_SIZE; ++i) {
        directions->directions[i] = NONE;
    }
}


unsigned get_direction(const Directions* directions) {
    return directions->directions[directions->curr]; 
}


unsigned shift_directions_up(Directions* directions) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;

    if(directions->curr < directions->end) {
        directions->curr++;
        return SUCCESS;
    } else {
        return FAILURE;
    }
}
