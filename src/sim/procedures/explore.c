/*
 * File: explore.c
 * Author: Paulo Lemus
 */

#include <stdio.h>

#include <micromouse/sim/display.h>
#include <micromouse/sim/procedures/explore.h>

#include <micromouse/core/maze/maze.h>
#include <micromouse/core/pathplanning/coord.h>
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/pathplanning/directions.h>
#include <micromouse/core/pathplanning/floodfill.h>


int proc_explore(
    const Maze* maze,
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
    Path path;

    // Initialization
    direction = NORTH;
    mouse_pos.x = 0;
    mouse_pos.y = 0;
    next_pos.x  = 0;
    next_pos.y  = 0;
    clear_maze(&ffMap);

    path.curr = 0;
    path.end  = 4;
    path.coords[0].x = 0;
    path.coords[0].y = 0;
    path.coords[1].x = 0;
    path.coords[1].y = 1;
    path.coords[2].x = 0;
    path.coords[2].y = 2;
    path.coords[3].x = 1;
    path.coords[3].y = 2;
    path.coords[4].x = 2;
    path.coords[4].y = 2;

    // Initialize ncurses display
    init_display();
    clear_display();
    put_posts(maze);
    put_hidden_walls(maze);
    put_path(maze, &path);
    put_mouse(maze, SOUTH, 0, 0);
    put_mouse(maze, NORTH, 0, 1);
    put_mouse(maze, EAST,  1, 0);
    put_mouse(maze, WEST,  1, 1);
    put_mouse(maze, NONE,  2, 2);
    render();
    getch();
    finish_display();
    return exit_code;
}
