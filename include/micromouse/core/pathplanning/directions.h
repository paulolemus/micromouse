/*
 * File: directions.h
 * Author: Paulo Lemus
 */

#ifndef MICROMOUSE_CORE_PATHPLANNING_DIRECTIONS_H_
#define MICROMOUSE_CORE_PATHPLANNING_DIRECTIONS_H_

#include <micromouse/config.h>

// Absolute directions - numbers are arbitrary
#define NORTH 10
#define SOUTH 20
#define WEST  30
#define EAST  40
#define NONE  50

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
    unsigned directions[DIRECTIONS_SIZE];
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
unsigned get_direction(const Directions* directions);

/**
 * @brief Move the direction up one.
 * @param directions Pointer to current direction.
 * @return 1 if success, 0 if fail.
 */
unsigned shift_directions_up(Directions* directions);


#endif // MICROMOUSE_CORE_PATHPLANNING_DIRECTIONS_H_
