/*
 * File     : maze.c
 * Author   : Paulo Lemus
 * Created  : 8/28/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>


unsigned set_maze_dimensions(
    Maze* maze,
    const unsigned width,
    const unsigned height
) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;

    if(width > MAX_WIDTH || height > MAX_HEIGHT) {
        return FAILURE;
    } else {
        maze->width = width;
        maze->height = height;
        return SUCCESS;
    }
}

/**
 * @brief Clear all the bits in a maze to 0.
 * @param maze A pointer to the maze.
 */
void clear_maze(Maze* maze) {
    unsigned i, j;
    for(i = 0; i != MAX_WIDTH; ++i) {
        for(j = 0; j != MAX_HEIGHT; ++j) {
            maze->maze[i][j] = 0;
        }
    }
}

void box_maze(
    Maze* maze
) {
    unsigned i;
    // Draw North and South walls
    for(i = 0; i != maze->width; ++i) {
        set_wall_on(maze, i, 0, SOUTH_WALL); 
        set_wall_on(maze, i, maze->height - 1, NORTH_WALL);
    }
    
    // Draw West and East walls
    for(i = 0; i != maze->height; ++i) {
        set_wall_on(maze, 0, i, WEST_WALL);
        set_wall_on(maze, maze->width - 1, i, EAST_WALL);
    }
}

void set_wall_on(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char wall
) {

    if(wall == NORTH_WALL) {

        maze->maze[x][y] |= wall;
        if(y + 1 < maze->height) {
            maze->maze[x][y + 1] |= SOUTH_WALL;
        }
    } else if(wall == SOUTH_WALL) {

        maze->maze[x][y] |= wall;
        if(y > 0) {
            maze->maze[x][y - 1] |= NORTH_WALL;
        }
    } else if(wall == EAST_WALL) {

        maze->maze[x][y] |= wall;
        if(x + 1 < maze->width) {
            maze->maze[x + 1][y] |= WEST_WALL;
        }
    } else if(wall == WEST_WALL) {

        maze->maze[x][y] |= wall;
        if(x > 0) {
            maze->maze[x - 1][y] |= EAST_WALL;
        }
    }
}

void set_wall_off(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char wall
) {
    if(wall == NORTH_WALL) {

        maze->maze[x][y] &= ~wall;
        if(y + 1 < maze->height) {
            maze->maze[x][y + 1] &= ~SOUTH_WALL;
        }
    } else if(wall == SOUTH_WALL) {

        maze->maze[x][y] &= ~wall;
        if(y > 0) {
            maze->maze[x][y - 1] &= ~NORTH_WALL;
        }
    } else if(wall == EAST_WALL) {

        maze->maze[x][y] &= ~wall;
        if(x + 1 < maze->width) {
            maze->maze[x + 1][y] &= ~WEST_WALL;
        }
    } else if(wall == WEST_WALL) {

        maze->maze[x][y] &= ~wall;
        if(x > 0) {
            maze->maze[x - 1][y] &= ~EAST_WALL;
        }
    }
}

unsigned has_wall(
    const Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char wall
) {
    if(maze->maze[x][y] & wall) return 1;
    else                        return 0;
}

void set_property_on(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char property 
) {
    if(property == VISITED ||
       property == UNCERTAIN) {
        maze->maze[x][y] |= property;
    }
}

void set_property_off(
    Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char property 
) {
    if(property == VISITED ||
       property == UNCERTAIN) {
        maze->maze[x][y] &= ~property;
    }
}

unsigned has_property(
    const Maze* maze,
    const unsigned x,
    const unsigned y,
    const unsigned char property
) {
    if(maze->maze[x][y] & property) return 1;
    else                            return 0;
}


