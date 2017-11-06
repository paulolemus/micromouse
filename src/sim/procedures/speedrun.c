/*
 * File: speedrun.c
 * Author: Paulo lemus
 */


#include <stdio.h>
#include <micromouse/config.h>

#include <micromouse/core/maze/maze.h>
#include <micromouse/core/pathplanning/coord.h>
#include <micromouse/core/pathplanning/directions.h>
#include <micromouse/core/pathplanning/path.h>

#include <micromouse/sim/display.h>
#include <micromouse/sim/base.h>
#include <micromouse/sim/procedures/speedrun.h>



int proc_speedrun(
    const Maze* maze
) {
    const int    SUCCESS   =   0;
    const int    FAILURE   =  -1;
    const double SPEED_ADJ = 0.1;

    int exit_code = FAILURE;

    // Variables
    Coord mouse_pos;
    Coord next_pos;
    Coord goal_pos;
    FloodObj floodObj;
    Path path;

    // Initializations
    Direct mouse_dir = NORTH;
    double speed = SIM_SPEED;
    int is_path_valid = 0;
    int show_path   = 1;
    int control     = 'p';
    int paused      = 1;
    int step        = 0;
    int finished    = 0;

    clear_path(&path);
    mouse_pos.x = 0;
    mouse_pos.y = 0;
    goal_pos.x  = 0;
    goal_pos.y  = 0;

    // Get goal coordinates and validate
    printf("Enter goal x coordinate: ");
    scanf("%u", &goal_pos.x);
    printf("Enter goal y coordinate: ");
    scanf("%u", &goal_pos.y);

    if(goal_pos.x >= maze->width || goal_pos.y >= maze->height) {
        printf("coordinates (%u, %u) are greater than maze bounds\n", 
                goal_pos.x, goal_pos.y);
        exit_code = FAILURE;
        finished = 1;
        control = 'q';
    } else {
        init_display();
    }

    // Primary solving loop
    while(control != 'q') {

        // Process keyboard input if any
        if(kbhit()) {
            control = getch();

            switch(control) {
            // Toggle paused state
            case 'p':
                paused = !paused;
                step = 0;
                break;
            // Reset speedrun 
            case 'r':
                step = 0;
                paused = 1;
                finished = 0;
                mouse_pos.x = 0;
                mouse_pos.y = 0;
                show_path   = 0;
                is_path_valid = 0;
                mouse_dir = NORTH;
                break;
            // Increase simulation speed
            case 'm':
                speed += SPEED_ADJ;
                break;
            // Decrease simulation speed
            case 'n':
                if(speed - SPEED_ADJ > 0.5) {
                    speed -= SPEED_ADJ;
                }
                break;
            // Toggle display of path
            case '1':
                show_path = !show_path;
                break;
            // Step simulation one cycle
            case 'o':
                step = 1;
                break;
            // Quit simulation
            case 'q':
                finished = 1;
                paused = 1;
                step = 0;
                break;
            default:
                break;
            }
        }


        // Stepping logic
        if(step && paused) {
            paused = 0;
        } else if(step) {
            paused = 1;
            step   = 0;
        }

        // Only consider movement if not finished
        if(finished || paused) {

        // Calculate a path from current location to goal
        } else if(!is_path_valid) {

            // Ensure floodfill ran successfully.
            if(!floodfill(&floodObj, maze, &goal_pos)) {
                exit_code = FAILURE;
                finished  = 1;
                control   = 'q';
            }
            // Extract path, and check for success.
            else if(!ff_get_path(&floodObj, maze, &mouse_pos, &path)) {
                exit_code = FAILURE;
                finished  = 1;
                control   = 'q';
            } else {
                next_pos.x = path.coords[0].x;
                next_pos.y = path.coords[0].y;
                is_path_valid = 1;
                show_path = 1;
            }
            
        // Move along valid path to goal if we are not there
        } else if(mouse_pos.x != goal_pos.x || mouse_pos.y != goal_pos.y) {

            // If we have reached next position, get the next position
            if(mouse_pos.x == next_pos.x && mouse_pos.y == next_pos.y) {
                next_pos = get_next_coord(&path);
                shift_path_up(&path);
            }

            // Determine what abs direction we need to move in
            Direct next_abs_dir;
            if(     mouse_pos.x > next_pos.x) next_abs_dir = WEST;
            else if(mouse_pos.x < next_pos.x) next_abs_dir = EAST;
            else if(mouse_pos.y > next_pos.y) next_abs_dir = SOUTH;
            else if(mouse_pos.y < next_pos.y) next_abs_dir = NORTH;

            // Convert direction to a relative direction
            Relative next_rel_dir = 
                direct_to_relative(mouse_dir, next_abs_dir);

            // Move according to relative direction
            move_sim_mouse(&mouse_pos, &mouse_dir, next_rel_dir);

        } else {
            exit_code = SUCCESS;
            finished = 1;
        }
         
        // Draw all structures to screen
        clear_display();
        put_posts(maze);
        put_visible_walls(maze);
        if(show_path) put_path(maze, &path);
        put_mouse(maze, mouse_dir, mouse_pos);
        render();

        if(!paused) sim_sleep(speed);
    }
    finish_display();
    return exit_code;
}

