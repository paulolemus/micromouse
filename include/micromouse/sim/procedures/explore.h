/* 
 * File: explore.h
 * Author: Paulo Lemus
 */

/*
 * Explore procedure
 *
 * Start mouse at starting coordiante.
 * Goal of procedure is for the mouse to explore every block in the maze.
 *
 * Controls:
 * q - quit
 * p - toggle play / pause
 * s - step
 * r - restart
 *
 * While procedure is paused, we can set new state values.
 */

#ifndef MICROMOUSE_SIM_PROCEDURES_EXPLORE_H_
#define MICROMOUSE_SIM_PROCEDURES_EXPLORE_H_

#include <micromouse/core/maze/maze.h>
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/pathplanning/directions.h>

/**
 * @brief Procedure to explore all blocks of a maze.
 * @param maze Completed maze.
 * @param mouseMaze Mouse's view of the maze.
 * @return 1 if successful, 0 if failure
 */
int proc_explore(
    const Maze* maze,
    Maze* mouseMaze
);



#endif // MICROMOUSE_SIM_PROCEDURES_EXPLORE_H_

