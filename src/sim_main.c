/**
 * File: sim_maze.c
 * Name: Paulo Lemus
 *
 * The maian driver program of the simulation.
 * What it does:
 * 1. Setup data structures for mouse's maze,
 *    the actual maze, and the floodfill maze.
 * 2. Initialize all the datas stuctures.
 * 3. Ask the user what operation to do.
 * 4. Depending on operation, use while loop to begin simulating
 *    the mouse searching the maze, and once its gathered enough
 *    information, head back to start. Then it will solve the maze.
 */

#include <stdio.h>

#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>
#include <micromouse/core/maze/parser.h>
#include <micromouse/sim/display.h>

int main() {

    // Variables with default values
    // Actual dimensions of maze
    unsigned width  = 16;
    unsigned height = 16;
    // Booleans to toggle views
    int show_hidden_walls = SHOW_HIDDEN_WALLS;
    int show_ff_values    = SHOW_FF_VALUES;
    int show_path         = SHOW_PATH;
    // Mouse variables
    unsigned x_pos = 0;
    unsigned y_pos = 0;
    unsigned dir = NORTH;
    const unsigned X_GOAL = (width  - 1) / 2;
    const unsigned Y_GOAL = (height - 1) / 2;

    // Maze data structures
    Maze maze;
    Maze mouseMaze;
    Maze ffMaze;

    // Clear mazes, ensure all bits are properly set. 
    clear_maze(&maze);
    clear_maze(&mouseMaze);
    clear_maze(&ffMaze);

    // Parse in mazes from default sim file named in config.h
    if(parse_maze(&maze, &width, &height, SIM_MAP_STR) == 0) {
        fprintf(stderr, "sim_main - Failed to parse maze\n");
        return (-1);
    }

    if(set_maze_dimensions(&maze, width, height)      == 0 ||
       set_maze_dimensions(&mouseMaze, width, height) == 0 ||
       set_maze_dimensions(&ffMaze, width, height)    == 0) {

        fprintf(stderr, "sim_main - Failed to set width and height\n");
        return (-1);
    }

    return 0;
}
