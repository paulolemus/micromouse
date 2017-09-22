/**
 * File     : config.h
 * Created  : 8/27/2017
 * Modified : 8/27/2017
 *
 * File that contains all global configuration files for the project.
 */

#ifndef MICROMOUSE_UNICORN_CONFIG_H_
#define MICROMOUSE_UNICORN_CONGIG_H_

/////////////////////
//   Maze config   //
/////////////////////

// Number of blocks horizontally
#define MAZE_BLOCKS_WIDTH 16
// Number of blocks vertically
#define MAZE_BLOCKS_HEIGHT 16

///////////////////////
//   Parser config   //
///////////////////////

#define DEFAULT_MAP_STR "src/default_map.data"
#define TOP_WALL_STR    "NORTH"
#define LEFT_WALL_STR   "WEST"
#define RIGHT_WALL_STR  "EAST"
#define BOTTOM_WALL_STR "SOUTH"
#define VISITED_STR     "VISITED"
#define UNCERTAIN_STR   "UNCERT"


#endif // MICROMOUSE_UNICORN_CONFIG_H_
