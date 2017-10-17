/*
 * File     : parser.c
 * Author   : Paulo Lemus
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>
#include <micromouse/coree/maze/parser.h>

/**
 * @brief Using the information parsed in from a single line of
 *        the maze data file, set the corresponding bit.
 * @param maze A 2D represention of the maze.
 * @param x The X coordinate of the block to set.
 * @param y The Y coordinate of the block to set.
 * @param str The string to switch.
 */
void setMazeBit(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT],
    unsigned int x,
    unsigned int y,
    const char* str
) {

    if(     !strcmp(str, TOP_WALL_STR))    setBitOn(maze, x, y, NORTH_WALL);
    else if(!strcmp(str, LEFT_WALL_STR))   setBitOn(maze, x, y, WEST_WALL);
    else if(!strcmp(str, RIGHT_WALL_STR))  setBitOn(maze, x, y, EAST_WALL);
    else if(!strcmp(str, BOTTOM_WALL_STR)) setBitOn(maze, x, y, SOUTH_WALL);
    else if(!strcmp(str, VISITED_STR))     setBitOn(maze, x, y, VISITED);
    else if(!strcmp(str, UNCERTAIN_STR))   setBitOn(maze, x, y, UNCERTAIN);
    else {
        perror("Error: parsed undefined token\n");
        exit(-1);
    }
}

unsigned int parse_maze(
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT],
    const char* fname
) {
    const unsigned int SUCCESS = 1;
    const unsigned int FAILURE = 0;
    const int BUF_SIZE = 100;

    char buffer[BUF_SIZE]; 

    // Open file and check for validity.
    FILE* fp = fopen(fname, "r");
    if(fp == NULL) {
        perror("Error: File cannot be opened\n");
        return FAILURE;
    }

    // Confirm that the parsed maze has the same dimensions
    // as the defined maze width and height.
    int width;
    int height;
    if(fgets(buffer, BUF_SIZE, fp) == NULL) {
        perror("Error: Could not parse first line\n");
        return FAILURE;
    }
    if(sscanf(buffer, "%d %d", &width, &height) != 2) {
        perror("Error: Could not parse width and height\n");
        return FAILURE;
    }
    if(width != MAZE_WIDTH || height != MAZE_HEIGHT) {
        perror("Error: Width and height of maze data do not match actual\n");
        return FAILURE;
    }

    // Good to parse the the maze data into the maze
    // Read line by line, tokenize line, pass values into
    // function to set bits in the maze pointer.
    while(fgets(buffer, BUF_SIZE, fp) != NULL) {
        unsigned int x;
        unsigned int y;
        const char delim[3] = ", ";
        char line[BUF_SIZE];
        char* token;

        // Copy string into line to prevent const string
        // modification errors with strtok.
        strcpy(line, buffer);
        
        // Get x and y
        token = strtok(line, delim);
        if(sscanf(token, "%d", &x) != 1) {
            perror("Error: Failed to parse x coord\n");
            return FAILURE;
        }
        token = strtok(NULL, delim);
        if(sscanf(token, "%d", &y)) {
            perror("Error: Failed to parse y coord\n");
            return FAILURE;
        }

        // Parse through tokens on line
        token = strtok(NULL, delim);
        while(token != NULL) {
            setMazeBit(maze, x, y, token);
            token = strtok(NULL, delim);
        }
    }
    return SUCCESS;
}


