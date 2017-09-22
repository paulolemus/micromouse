/*
 * File     : parser.c
 * Author   : Paulo Lemus
 * Created  : 9/21/17
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <micromouse/config.h>
#include <micromouse/core/maze/parser.h>
#include <micromouse/core/maze/maze.h>


/*
 * Evaluate token and set whatever bit in the block that it corresponds to.
 * Note that if a token does not match any of the defined tokens, an error 
 * is thrown.
 *
 * *_STR tokens can be found in config.h
 * M_*   tokens can be found in maze.h
 */
void setMazeBit(struct Maze* maze, unsigned int x, unsigned int y, char* token) {
    if(!strcmp(token,      TOP_WALL_STR))    setBitOn(maze, x, y, M_NORTH_WALL);
    else if(!strcmp(token, LEFT_WALL_STR))   setBitOn(maze, x, y, M_WEST_WALL);
    else if(!strcmp(token, RIGHT_WALL_STR))  setBitOn(maze, x, y, M_EAST_WALL);
    else if(!strcmp(token, BOTTOM_WALL_STR)) setBitOn(maze, x, y, M_SOUTH_WALL);
    else if(!strcmp(token, VISITED_STR))     setBitOn(maze, x, y, M_VISITED);
    else if(!strcmp(token, UNCERTAIN_STR))   setBitOn(maze, x, y, M_UNCERTAIN);
    else {
        perror("Error: Invalid token");
        exit(EXIT_FAILURE);
    }
}


/*
 * If the parser cannot read a file in, return NULL.
 * If the parser encounters an error while parsing in
 * a file that exists, the file was incorrectly written 
 * and we stop the program.
 *
 * We use parser config definitions from the config.h file.
 * TOP_WALL_STR    : NORTH
 * LEFT_WALL_STR   : WEST
 * RIGHT_WALL_STR  : EAST
 * BOTTOM_WALL_STR : SOUTH
 *
 * File format:
 * two ints representing width and height respectively.
 * {x},{y} ARG1 ARG2 ...
 */
struct Maze* parseMaze(char* filename) {

    unsigned int width;
    unsigned int height;
    struct Maze* maze = NULL;

    char buffer[50];
    FILE* file = fopen(filename, "r");

    if(file) {
        
        // Get width and height, create maze
        fgets(buffer, 50, file);
        sscanf(buffer, "%u %u\n", &width, &height);
        maze = newMaze(width, height);

        // Loop through rest of file parsing tokens
        char* token = NULL;
        for(unsigned int i = 0; i < width; ++i) {
            for(unsigned int j = 0; j < height; ++j) {

                // Error check while getting line
                if(fgets(buffer, 50, file) == NULL) {
                    perror("Error: Parsing file");
                    exit(EXIT_FAILURE);
                }

                // Sanitize buffer
                char* newline = strchr(buffer, '\n');
                if(newline) *newline = 0;

                // Parse row,col
                unsigned int x;
                unsigned int y;
                char* copy = strdup(buffer);
                token = strtok(copy, " ");
                sscanf(token, "%u,%u", &x, &y);
                
                // Parse bit tokens
                token = strtok(NULL, " ");
                while(token != NULL) {
                    setMazeBit(maze, x, y, token);
                    token = strtok(NULL, " ");
                }
                free(copy);
            }
        }

    } 
    return maze;
}
