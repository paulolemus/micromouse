/*
 * File: display.c
 * Author: Paulo Lemus
 */

#include <stdlib.h>
#include <ncurses.h>

#include <micromouse/core/maze/maze.h>
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/pathplanning/directions.h>
#include <micromouse/sim/display.h>

#define SCALE_X 4
#define SCALE_Y 2
#define OFFSET_X 2
#define OFFSET_Y 1

void init_display() {

    // Init, get input immediately
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Init Colors
    use_default_colors();
    start_color();
    // Default color pairing
    init_pair(1, COLOR_WHITE, -1);
    // Main Path color
    init_pair(2, -1, COLOR_GREEN);
    // invalid text
    init_pair(3, COLOR_RED, -1);

    // Set defaults
    bkgd(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
}

void clear_display() {
    erase();
}

void render() {
    refresh();
}

void finish_display() {
    endwin();
}

void put_mouse(
    const Maze* maze,
    const Direct direction,
    const Coord coord
) {
    // Convert to row and column
    int row = abs(coord.y - maze->height + 1) * SCALE_Y + OFFSET_Y;
    int col = coord.x * SCALE_X + OFFSET_X;

    switch(direction) {
    case NORTH:
        mvaddch(row, col, '^');
        break;
    case SOUTH:
        mvaddch(row, col, 'v'); 
        break;
    case EAST:
        mvaddch(row, col, '>');
        break;
    case WEST:
        mvaddch(row, col, '<');
        break;
    default:
        mvaddch(row, col, ACS_DIAMOND);
        break;
    }
}

void put_posts(
    const Maze* maze
) {
    for(int i = 0; i <= maze->width; ++i) {
        for(int j = 0; j <= maze->height; ++j) {
            mvaddch(j * SCALE_Y, i * SCALE_X, '+');
        }
    }
}

void put_hidden_walls(
    const Maze* maze
) {
    attroff(A_BOLD);
    attron(A_DIM);
    put_visible_walls(maze);
    attroff(A_DIM);
    attron(A_BOLD);
}

void put_visible_walls(
    const Maze* maze
) {
    for(unsigned x = 0; x < maze->width; ++x) {
        for(unsigned y = 0; y < maze->height; ++y) {
            
            // Convert to row and column
            int row = abs(y - maze->height + 1) * SCALE_Y + OFFSET_Y;
            int col = x * SCALE_X + OFFSET_X;

            if(has_wall(maze, x, y, NORTH_WALL)) {
                mvaddch(row - OFFSET_Y, col - 1, ACS_HLINE); 
                mvaddch(row - OFFSET_Y, col,     ACS_HLINE); 
                mvaddch(row - OFFSET_Y, col + 1, ACS_HLINE); 
            }
            if(has_wall(maze, x, y, SOUTH_WALL)) {
                mvaddch(row + OFFSET_Y, col - 1, ACS_HLINE); 
                mvaddch(row + OFFSET_Y, col,     ACS_HLINE); 
                mvaddch(row + OFFSET_Y, col + 1, ACS_HLINE); 
            }
            if(has_wall(maze, x, y, EAST_WALL)) {
                mvaddch(row, col + OFFSET_X, ACS_VLINE); 
            }
            if(has_wall(maze, x, y, WEST_WALL)) {
                mvaddch(row, col - OFFSET_X, ACS_VLINE); 
            }
        }
    }
}

void put_path(
    const Maze* maze,
    const Path* path
) {
    attron(COLOR_PAIR(2));
    for(unsigned i = path->curr; i <= path->end; ++i) {
        int row = abs(path->coords[i].y - maze->height + 1) * SCALE_Y + OFFSET_Y;
        int col = path->coords[i].x * SCALE_X + OFFSET_X;
        mvaddch(row, col, ' ');

        // Color the block in the direction of the next coordinate.
        if(i < path->end) {
            int x_dir = (int)path->coords[i + 1].x - (int)path->coords[i].x;
            int y_dir = (int)path->coords[i + 1].y - (int)path->coords[i].y;

            if(x_dir) {
                mvaddch(row, col + x_dir,     ' ');
                mvaddch(row, col + x_dir * 2, ' ');
                mvaddch(row, col + x_dir * 3, ' ');
            } else if(y_dir) {
                mvaddch(row - y_dir, col, ' ');
            }
        }
    }
    attroff(COLOR_PAIR(2));
}
