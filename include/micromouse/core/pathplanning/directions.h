/*
 * File: directions.h
 * Author: Paulo Lemus
 */

#ifndef MICROMOUSE_CORE_PATHPLANNING_DIRECTIONS_H_
#define MICROMOUSE_CORE_PATHPLANNING_DIRECTIONS_H_

#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>

/*
 * Absolute directions.
 * Ensure that these are order clockwise or counterclockwise.
 */
typedef enum Direct {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    DIRECT_COUNT 
} Direct;

/*
 * Relative directions.
 * Ensure that these are order clockwise or counterclockwise.
 */
typedef enum Relative {
    FORWARD,
    RIGHT,
    BACK,
    LEFT,
    RELATIVE_COUNT
} Relative;

/**
 * @brief Convert a relative direction to an absolute direction.
 * @param direction Current mouse absolute direction.
 * @param relative Direction relative to absolute direction.
 * @return Direct of converted relative to absolutee direction.
 */
Direct relative_to_direct(
    Direct mouse_dir,
    Relative relative
);

Relative direct_to_relative(
    Direct mouse_dir,
    Direct new_dir 
);

/**
 * @brief Convert a relative direction to wall constant.
 * @param direction Current mouse absolute direction.
 * @param relative Direction relative to absolute direction.
 * @return Wall constant defined in maze.h.
 */
unsigned char relative_to_wall(
    Direct mouse_dir,
    Relative relative
);

/**
 * Directions struct is used to represent the directions that
 * something needs to take to get from current location to a target.
 *
 * @field curr Index of the current move that needs to be taken.
 * @field end Index of the last directions to take to get to goal.
 * @field directions The array holding the directions.
 */
typedef struct Directions {
    unsigned curr;
    unsigned end;
    Direct directions[DIRECTIONS_SIZE];
} Directions;

/**
 * @brief Initialization function for Directions struct.
 *        Clears all fields to default state.
 * @param directions A pointer to a Directions struct.
 */
void clear_directions(Directions* directions);

/**
 * @brief Get the next direction to move in.
 * @param directions A pointer to the current Directions struct.
 * @return value equal to one of the directions defined in directions.h
 */
Direct get_direction(const Directions* directions);

/**
 * @brief Move the direction up one.
 * @param directions Pointer to current direction.
 * @return 1 if success, 0 if fail.
 */
unsigned shift_directions_up(Directions* directions);


#endif // MICROMOUSE_CORE_PATHPLANNING_DIRECTIONS_H_
