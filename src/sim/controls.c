/*
 * File: controls.c
 * Author: Paulo Lemus
 */

#include <ncurses.h>
#include <micromouse/sim/controls.h>

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
