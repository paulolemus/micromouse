/*
 * File     : parser.c
 * Author   : Paulo Lemus
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>
#include <micromouse/core/maze/parser.h>

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
        fprintf(stderr, "setMazeBit - undefined token = %s\n", str);
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
        fprintf(stderr, "parse_maze - could not parse first line\n");
        fclose(fp);
        return FAILURE;
    }
    if(sscanf(buffer, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "parse_maze - Could not parse width and height\n");
        fclose(fp);
        return FAILURE;
    }
    if(width > MAZE_WIDTH || height > MAZE_HEIGHT) {
        fprintf(stderr, "parse_maze - Width and height of greater than allowed\n");
        fclose(fp);
        return FAILURE;
    }

    // Good to parse the the maze data into the maze
    // Read line by line, tokenize line, pass values into
    // function to set bits in the maze pointer.
    while(fgets(buffer, BUF_SIZE, fp) != NULL) {
        unsigned int x;
        unsigned int y;
        const char delim[3] = ", \n";
        char line[BUF_SIZE];
        char* token;

        // Copy string into line to prevent const string
        // modification errors with strtok.
        strcpy(line, buffer);
        
        // Get x and y
        token = strtok(line, delim);
        if(sscanf(token, "%u", &x) != 1) {
            fprintf(stderr, "parse_maze - Failed to parse x coord\n");
            fclose(fp);
            return FAILURE;
        }
        token = strtok(NULL, delim);
        if(sscanf(token, "%u", &y) != 1) {
            fprintf(stderr, "parse_maze - Failed to parse y coord\n");
            fclose(fp);
            return FAILURE;
        }

        // Parse through tokens on line
        token = strtok(NULL, delim);
        while(token != NULL) {
            setMazeBit(maze, x, y, token);
            token = strtok(NULL, delim);
        }
    }
    fclose(fp);
    return SUCCESS;
}


