/**
 * File:
 *     floodfill.h
 *
 * Description:
 *     Floodfill is a simple algorithm that ranks the area connected to a given
 *     node. It behaves as if a bucket of water was poured in the target square
 *     and it marks every node is passes over equal to the distance that water
 *     has traveled.
 *
 *     This is used with the Maze to build a "shortest" path from a given node
 *     to the target node.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_CORE_FLOODFILL_H_
#define MICROMOUSE_CORE_FLOODFILL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "micromouse/config.h"
#include "micromouse/core/maze.h"


// Storage for floodfill generated data.
typedef struct FloodObj {
    unsigned char map[MAX_WIDTH][MAX_HEIGHT];
} FloodObj;

/**
 * @brief Perform floodfill algorithm with given maze and goal
 *        coordinates, and store the processed values in the floodObj.
 * @param floodObj Store for the floodfill map.
 * @param maze A pointer to the maze to flood.
 * @param target Coordinates of the goal cell.
 * @return 1 if success, 0 if failure.
 */
unsigned floodfill(
    FloodObj* floodObj, 
    const Maze* maze, 
    const Coord* target
);


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_CORE_FLOODFILL_H_
