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
#include <micromouse/maze/maze.h>

int main() {

    // Maze data structures
    BLOCK maze[SIM_MAZE_WIDTH][SIM_MAZE_HEIGHT];
    BLOCK mouseMaze[SIM_MAZE_WIDTH][SIM_MAZE_HEIGHT];
    BLOCK ffMaze[SIM_MAZE_WIDTH][SIM_MAZE_HEIGHT];

    // Clear mazes, ensure all bits are properly set. 
    clear_maze(maze);
    clear_maze(mouseMaze);
    clear_maze(ffMaze);

    // Parse in mazes from default sim file named in config.h



    return 0;
}
