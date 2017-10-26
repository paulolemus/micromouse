/*
 * File: display.c
 * Author: Paulo Lemus
 */

#include <ncurses.h>

#include <micromouse/core/maze/maze.h>
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/pathplanning/directions.h>
#include <micromouse/sim/display.h>


void init_display() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    printw("Init_display!\n");
    refresh();
    getch();
}

void clear_display() {

}

void render() {
    refresh();
}

void finish_display() {
    endwin();
}

void put_mouse(
    const Direct direction,
    const unsigned x,
    const unsigned y
) {

}

void put_hidden_walls(
    const Maze* maze
) {

}

void put_visible_walls(
    const Maze* maze
) {

}

void put_path(
    const Path* path
) {

}
