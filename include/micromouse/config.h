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

// MAX maze dimensions
#define MAX_WIDTH  16
#define MAX_HEIGHT 16


/////////////////////////////
//   Pathplanning config   //
/////////////////////////////

// Path default length
#define PATH_SIZE 64
// Directions default length
#define DIRECTIONS_SIZE 64


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

// Simulator default variables
// Blocks traversed per second
#define SIM_SPEED 0.75


#endif // MICROMOUSE_UNICORN_CONFIG_H_
