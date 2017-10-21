/*
 * File: display.c
 * Author: Paulo Lemus
 */

#include <ncurses.h>
#include <micromouse/core/maze/maze.h>
#include <micromouse/sim/display.h>

void init_display(
    const unsigned int width,
    const unsigned int height
) {
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
    const unsigned int dir,
    const unsigned int x,
    const unsigned int y
) {

}

void put_hidden_walls(
    const unsigned int WIDTH,
    const unsigned int HEIGHT,
    BLOCK maze[WIDTH][HEIGHT] 
) {

}

void put_visible_walls(
    const unsigned int WIDTH,
    const unsigned int HEIGHT,
    BLOCK maze[WIDTH][HEIGHT] 
) {

}

void put_path() {

}
