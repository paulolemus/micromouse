/*
 * File: explore.c
 * Author: Paulo Lemus
 */

#include <micromouse/sim/display.h>
#include <micromouse/sim/procedures/explore.h>

#include <micromouse/core/maze/maze.h>
#include <micromouse/core/pathplanning/coord.h>
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/pathplanning/directions.h>
#include <micromouse/core/pathplanning/floodfill.h>


int proc_explore(
    Maze* maze,
    Maze* mouseMaze
) {
    const int SUCCESS = 1;
    const int FAILURE = 0;

    int exit_code = SUCCESS;

    // Variables
    Direct direction;
    Coord mouse_pos;
    Coord next_pos;
    Maze ffMap;

    // Initialization
    direction = NORTH;
    mouse_pos.x = 0;
    mouse_pos.y = 0;
    next_pos.x  = 0;
    next_pos.y  = 0;

    // Initialize ncurses display
    init_display();
    clear_display();
    put_visible_walls(maze);
    render();
    getch();
    finish_display();

    return exit_code;
}
