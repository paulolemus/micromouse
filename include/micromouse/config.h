/**
 * File     : config.h
 * Created  : 8/27/2017
 * Modified : 8/27/2017
 *
 * File that contains all global configuration files for the project.
 * 
 * The program looks to this file to set up all data structures statically.
 * Keep in mind that the data structures for the maze representations are
 * 2D arrays.
 */

#ifndef MICROMOUSE_UNICORN_CONFIG_H_
#define MICROMOUSE_UNICORN_CONFIG_H_

/////////////////////
//   Maze config   //
/////////////////////

// Primary maze dimensions
#define MAZE_WIDTH  16
#define MAZE_HEIGHT 16


///////////////////////
//   Parser config   //
///////////////////////

#define DEFAULT_MAP_STR "../src/default_map.data"
#define TOP_WALL_STR    "NORTH"
#define LEFT_WALL_STR   "WEST"
#define RIGHT_WALL_STR  "EAST"
#define BOTTOM_WALL_STR "SOUTH"
#define VISITED_STR     "VISITED"
#define UNCERTAIN_STR   "UNCERT"


///////////////////////
// Simulation Config //
///////////////////////

// File containing maze data
#define SIM_MAP_STR "../src/sim/default_sim_maze.data"


#endif // MICROMOUSE_UNICORN_CONFIG_H_
