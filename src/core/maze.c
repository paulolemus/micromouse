/**
 * File:
 *     maze.c
 *
 * Description:
 *     Implementation for maze data model functions.
 * 
 * Notes:
 * 
 *
 * Author:
 *     Paulo Lemus
 */

#include <stdbool.h>

#include "micromouse/config.h"
#include "micromouse/core/maze.h"


unsigned init_maze(
    Maze* maze,
    const unsigned width,
    const unsigned height
) {
    unsigned i, j;

    if(width > MAX_WIDTH || height > MAX_HEIGHT) {
        return false;
    }

    maze->width = width;
    maze->height = height;

    for(i = 0; i != MAX_WIDTH; ++i) {
        for(j = 0; j != MAX_HEIGHT; ++j) {
            maze->maze[i][j] = 0;
        }
    }
    return true;
}


void box_maze(
    Maze* maze
) {
    unsigned i;

    // Draw North and South walls.
    for(i = 0; i != maze->width; ++i) {
        set_field_on(maze, i, 0, WALL_SOUTH);
        set_field_on(maze, i, maze->height - 1, WALL_NORTH);
    }

    // Draw West and East walls.
    for(i = 0; i != maze->height; ++i) {
        set_field_on(maze, 0, i, WALL_WEST);
        set_field_on(maze, maze->width - 1, i, WALL_EAST);
    }
}


void set_field_on(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const cell_t mask
) {
   if(mask == WALL_NORTH) {

        maze->maze[x][y] |= (cell_t) WALL_NORTH;
        if(y + 1 < maze->height) {
            maze->maze[x][y + 1] |= (cell_t) WALL_SOUTH;
        }

    } else if(mask == WALL_SOUTH) {

        maze->maze[x][y] |= (cell_t) WALL_SOUTH;
        if(y > 0) {
            maze->maze[x][y - 1] |= (cell_t) WALL_NORTH;
        }

    } else if(mask == WALL_EAST) {

        maze->maze[x][y] |= (cell_t) WALL_EAST;
        if(x + 1 < maze->width) {
            maze->maze[x + 1][y] |= (cell_t) WALL_WEST;
        }

    } else if(mask == WALL_WEST) {

        maze->maze[x][y] |= (cell_t) WALL_WEST;
        if(x > 0) {
            maze->maze[x - 1][y] |= (cell_t) WALL_EAST;
        }

	} 
}


void set_field_off(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const cell_t mask
) {
	if(mask == WALL_NORTH) {

        maze->maze[x][y] &= (cell_t) ~((unsigned) WALL_NORTH);
        if(y + 1 < maze->height) {
            maze->maze[x][y + 1] &= (cell_t) ~((unsigned) WALL_SOUTH);
        }

    } else if(mask == WALL_SOUTH) {

        maze->maze[x][y] &= (cell_t) ~((unsigned) WALL_SOUTH);
        if(y > 0) {
            maze->maze[x][y - 1] &= (cell_t) ~((unsigned) WALL_NORTH);
        }

    } else if(mask == WALL_EAST) {

        maze->maze[x][y] &= (cell_t) ~((unsigned) WALL_EAST);
        if(x + 1 < maze->width) {
            maze->maze[x + 1][y] &= (cell_t) ~((unsigned) WALL_WEST);
        }

    } else if(mask == WALL_WEST) {

        maze->maze[x][y] &= (cell_t) ~((unsigned) WALL_WEST);
        if(x > 0) {
            maze->maze[x - 1][y] &= (cell_t) ~((unsigned) WALL_EAST);
        }

	}
}


unsigned has_field(
    const Maze* maze,
    const unsigned x,
    const unsigned y,
    const cell_t mask
) {
    if(maze->maze[x][y] & mask) return true;
    else                        return false;
}
