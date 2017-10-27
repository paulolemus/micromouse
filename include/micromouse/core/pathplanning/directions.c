/*
 * File: directions.c
 * Author: Paulo Lemus
 */

#include <micromouse/config.h>
#include <micromouse/core/pathplanning/directions.h>


Direct relative_to_direct(
    Direct mouse_dir,
    Relative relative
) {
    return (mouse_dir + relative) % DIRECT_COUNT;
}

unsigned char relative_to_wall(
    Direct mouse_dir,
    Relative relative
) {
    Direct dir = relative_to_direct(mouse_dir, relative);
    switch(dir) {
    case NORTH: return NORTH_WALL;
    case EAST : return EAST_WALL;
    case SOUTH: return SOUTH_WALL;
    case WEST : return WEST_WALL;
    default   : return 0;
    }
}

void clear_directions(Directions* directions) {
    directions->curr = 0;
    directions->end  = 0;
    for(unsigned i = 0; i < DIRECTIONS_SIZE; ++i) {
        directions->directions[i] = DIRECT_COUNT;
    }
}


Direct get_direction(const Directions* directions) {
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
