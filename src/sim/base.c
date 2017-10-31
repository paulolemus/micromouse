/*
 * File: base.c
 * Author: Paulo Lemus
 */

#include <unistd.h>
#include <ncurses.h>
#include <micromouse/sim/base.h>


int kbhit() {

    nodelay(stdscr, TRUE);
    int c = getch();
    nodelay(stdscr, FALSE);

    if(c != ERR) {
        ungetch(c);
        return 1;
    } else {
        return 0;
    }
}

void sim_sleep(
    const double speed
) {
    const unsigned SECOND = 1000000;
    unsigned time_to_wait = SECOND / speed;

    while(time_to_wait > SECOND) {
        sleep(1);
        time_to_wait -= SECOND;
    }
    usleep(time_to_wait);
}


/**
 * Helper function for mouse_sim_mouse
 */
void move_mouse_forward(
    Coord* mouse_pos,
    const Direct* mouse_dir
) {
    switch(*mouse_dir) {
    case NORTH: mouse_pos->y++; break;
    case SOUTH: mouse_pos->y--; break;
    case EAST : mouse_pos->x++; break;
    case WEST : mouse_pos->x--; break;
    default   : break;
    }
}

void move_sim_mouse(
    Coord* mouse_pos,
    Direct* mouse_dir,
    const Relative movement 
) {
    if(movement == FORWARD) {
        move_mouse_forward(mouse_pos, mouse_dir);
    } else if(movement == BACK) {
        *mouse_dir = relative_to_direct(*mouse_dir, RIGHT);
    } else {
        *mouse_dir = relative_to_direct(*mouse_dir, movement);
    }
}

