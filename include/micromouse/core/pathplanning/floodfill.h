/*
 * File     : floodfill.h
 * Author   : Paulo Lemus
 * Created  : 9/22/2017
 */

/*
 * Floodfill is an algorithm that here determines the distance from 
 * any point in a 2D array to a goal point. A quick way of visualizing
 * the floodfill algorithm:
 * Pour a bucket of water into your goal square, and keep pouring until
 * every square in the maze that can be reached from the goal has been 
 * covered.
 * Give each square a number equal to the distance the water had to travel
 * to get from the goal to the current square.
 * Goal would be 0, the squares surrounding goal would be 1, and so on.
 *
 * With a matrix with these processed values, we can then extract a 
 * path from any coordinate to that goal.
 *
 * Implementation:
 * Currently reusing a Maze struct to store the floodfill processed values.
 */

#ifndef MICROMOUSE_UNICORN_PATHPLANNING_FLOODFILL_H_
#define MICROMOUSE_UNICORN_PATHPLANNING_FLOODFILL_H_

#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/pathplanning/directions.h>


/**
 * @brief Perform floodfill algorithm with given maze and goal
 *        coordinates, and store the processed values in the ffMap.
 * @param maze A pointer to the maze to flood.
 * @param ffMap A pointer to the maze to store the processed map
 *              data in.
 * @param x X coordinate of goal.
 * @param y Y coordinate of goal.
 * @return 1 if success, 0 if failure
 */
unsigned floodfill(
    const Maze* maze, 
    Maze* ffMap, 
    const unsigned x_goal,
    const unsigned y_goal
);

/**
 * @brief Extract a path from a ffMap.
 * @param maze Used for wall data.
 * @param ffMap Floodfill data
 * @param x Current X coordinate
 * @param y Current Y coordinate
 * @param path Struct to populate with path data.
 * @return 1 if success, 0 if failure.
 */
unsigned ff_get_path(
    const Maze* maze,
    const Maze* ffMap,
    const unsigned x,
    const unsigned y,
    Path* path
);

/**
 * @brief Extract directions from a ffMap.
 * @param maze Maze used for wall data.
 * @param ffMap Map used for floodfill data.
 * @param x Current X coordinate.
 * @param y Current Y coordinate.
 * @param directions Struct to populate with directions.
 * @return 1 if success, 0 if failure.
 */
unsigned ff_get_directions(
    const Maze* maze,
    const Maze* ffMap,
    const unsigned x,
    const unsigned y,
    Directions* directions
);


#endif // MICROMOUSE_UNICORN_PATHPLANNING_FLOODFILL_H_
