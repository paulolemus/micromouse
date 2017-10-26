/**
 * File: sim_maze.c
 * Name: Paulo Lemus
 *
 * The maian driver program of the simulation.
 * What it does:
 * 1. Setup data structures for mouse's maze,
 *    the actual maze, and the floodfill maze.
 * 2. Initialize all the datas stuctures.
 * 3. Ask the user what operation to do.
 * 4. Depending on operation, use while loop to begin simulating
 *    the mouse searching the maze, and once its gathered enough
 *    information, head back to start. Then it will solve the maze.
 */

#include <stdio.h>

#include <micromouse/config.h>
#include <micromouse/core/maze/maze.h>
#include <micromouse/core/maze/parser.h>

#include <micromouse/sim/procedures/explore.h>
#include <micromouse/sim/procedures/speedrun.h>

/*
 * Main:
 * 1. Make Maze, mouseMaze, and ffObject. These are
 *    passed in to each procedure that uses them.
 * 2. This program selects which simulation procedure
 *    to launch.
 * 3. Continue running simulations until q has been entered.
 */
int main() {

    // Variables with default values
    // Actual dimensions of maze
    unsigned width  = MAX_WIDTH;
    unsigned height = MAX_HEIGHT;

    // Maze data structures
    Maze maze;
    Maze mouseMaze;

    // Clear mazes, ensure all bits are properly set. 
    clear_maze(&maze);
    clear_maze(&mouseMaze);

    // Parse in mazes from default sim file named in config.h
    if(parse_maze(&maze, &width, &height, SIM_MAP_STR) == 0) {
        fprintf(stderr, "sim_main - Failed to parse maze\n");
        return (-1);
    }

    if(set_maze_dimensions(&maze, width, height)      == 0 ||
       set_maze_dimensions(&mouseMaze, width, height) == 0) {

        fprintf(stderr, "sim_main - Failed to set width and height\n");
        return (-1);
    }


    /*
     * Get user input to select procedure to launch until q is entered.
     */
    int choice = ' ';
    int c;
    do {
        printf("\n1 - explore, 2 - speedrun\n");
        printf("Select procedure (q to quit): ");
        choice = getchar();

        // Clear stdin
        c = getchar();
        while(choice != EOF && c != '\n') {
            c = getchar();
        }

        // Select procedure
        switch(choice) {
        case '1':
            printf(
                "explore exit code: %d\n", 
                proc_explore(&maze, &mouseMaze)
            );
            break;
        case '2':
            printf(
                "speedrun exit code: %d\n", 
                proc_speedrun(&maze, &mouseMaze)
            );
            break;
        default:
            printf("case default\n");
            break;
        }
    } while(choice != 'q' && choice != EOF);

    printf("\n\nGoodbye!\n\n");
    return 0;
}




