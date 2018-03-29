/**
 * File:
 *     config.h
 *
 * Description:
 *     Global configuration parameters for micromouse.
 *
 * Notes:
 *     Defining certain parameters as macros allows for optimizations that may
 *     be necessary to keep the operations on the PIC MCU as lightweight as
 *     possible.
 *
 *     Various parameters can be changed to accomodate different evironments.
 *     
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_CONFIG_H_
#define MICROMOUSE_CONFIG_H_

// Frequency in Hz of mouse
#define _XTAL_FREQ 32000000

/////////////////////
//   Maze config   //
/////////////////////

// MAX maze dimensions
#define MAX_WIDTH  16
#define MAX_HEIGHT 16

//////////////////////////
//      ADC config      //
//////////////////////////

// ADC update frequency in us (1 ms)
#define ADC_DT 1000
// How many recent scans are averaged for a read?
// Ex: 4 means the last 4 scans are averaged and returned.
#define ADC_AVG 4

// Default value for sensor "wall is close" threshold.
// TODO: FIX DEFAULT VALUES
#define DEFAULT_LL_CLOSE 450
#define DEFAULT_LF_CLOSE 100
#define DEFAULT_RR_CLOSE 500
#define DEFAULT_RF_CLOSE 100


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


///////////////////////////
//   Simulation Config   //
///////////////////////////

// File containing maze data
#define SIM_MAP_STR "../src/sim/default_sim_maze.data"

// Simulator default variables
// Blocks traversed per second
#define SIM_SPEED 1.5


#endif // MICROMOUSE_CONFIG_H_
