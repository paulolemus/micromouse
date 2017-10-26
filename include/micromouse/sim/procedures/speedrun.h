/* 
 * File: speedrun.h
 * Author: Paulo Lemus
 */

/*
 * Speedrun procedure
 *
 * With a goal, completed maze, and current location,
 * navigate to the goal as quickly as possible.
 */

#ifndef MICROMOUSE_SIM_PROCEDURES_SPEEDRUN_H_
#define MICROMOUSE_SIM_PROCEDURES_SPEEDRUN_H_

#include <micromouse/core/maze/maze.h>

/**
 * @brief Procedure to navigate from start to goal over shortest path.
 * @param maze Completed maze
 * @param mouseMaze Mouse vision of maze
 * @return 1 if success, 0 if failure
 */
int proc_speedrun(
    Maze* maze,
    Maze* mouseMaze
);


#endif // MICROMOUSE_SIM_PROCEDURES_SPEEDRUN_H_
