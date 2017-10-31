/*
 * File: explore.c
 * Author: Paulo Lemus
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include <micromouse/config.h>
#include <micromouse/sim/display.h>
#include <micromouse/sim/controls.h>
#include <micromouse/sim/procedures/explore.h>

#include <micromouse/core/maze/maze.h>
#include <micromouse/core/pathplanning/coord.h>
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/pathplanning/directions.c>
#include <micromouse/core/pathplanning/floodfill.h>

typedef enum Explore_Mode {
    RIGHT_HUGGER,
    LEFT_HUGGER,
    FLOODFILL
} Explore_Mode;


void init_vars(
    const Maze* maze,
    Maze* mouseMaze,
    Maze* ffMap,
    Path* path,
    Coord* mouse_pos,
    Coord* next_pos,
    Coord* goal_pos
) {
    clear_maze(mouseMaze);
    clear_maze(ffMap);
    set_maze_dimensions(mouseMaze, maze->width, maze->height);
    box_maze(mouseMaze);

    // TODO: Figure out why clear_path(Path* path) does not work.
    path->curr = 0;
    path->end  = 0;
    for(unsigned i = 0; i < PATH_SIZE; ++i) {
        path->coords[i].x = 0;
        path->coords[i].y = 0;
    }
    mouse_pos->x = 0;
    mouse_pos->y = 0;
    next_pos->x  = 0;
    next_pos->y  = 0;
    goal_pos->x  = 0;
    goal_pos->y  = 0;
}

// greater the speed, less we wait.
void my_sleep(double speed) {

    const unsigned SECOND = 1000000;
    unsigned time_to_wait = SECOND / speed;

    while(time_to_wait > SECOND) {
        sleep(1);
        time_to_wait -= SECOND;
    }
    usleep(time_to_wait);
}


/*
 * Function used to check the wall in front, left, and right 
 * of the mouse, and then update the mouseMaze with that data.
 */
void update_walls(
    const Maze* maze,
    Maze* mouseMaze,
    Coord pos,
    Direct mouse_dir
) {
    unsigned char wall_def = relative_to_wall(mouse_dir, FORWARD);
    if(has_wall(maze, pos.x, pos.y, wall_def)) {
        set_wall_on(mouseMaze, pos.x, pos.y, wall_def);
    }
    wall_def = relative_to_wall(mouse_dir, LEFT);
    if(has_wall(maze, pos.x, pos.y, wall_def)) {
        set_wall_on(mouseMaze, pos.x, pos.y, wall_def);
    }
    wall_def = relative_to_wall(mouse_dir, RIGHT);
    if(has_wall(maze, pos.x, pos.y, wall_def)) {
        set_wall_on(mouseMaze, pos.x, pos.y, wall_def);
    }
}

/* 
 * Function used to place a mouse one position forward
 */
void move_mouse_forward(
    Coord* mouse_pos,
    Direct direction
) {
    switch(direction) {
    case NORTH:
        mouse_pos->y++;
        break;
    case SOUTH:
        mouse_pos->y--;
        break;
    case EAST:
        mouse_pos->x++;
        break;
    case WEST:
        mouse_pos->x--;
        break;
    default:
        break;
    }
}


int proc_explore(
    const Maze* maze,
    Maze* mouseMaze
) {
    const int SUCCESS =  0;
    const int FAILURE = -1;
    const double SPEED_ADJ = 0.1;

    int exit_code = SUCCESS;

    // Variables
    Coord mouse_pos;
    Coord next_pos;
    Coord goal_pos;
    Maze ffMap;
    Path path;

    // Initializations
    double speed = SIM_SPEED;
    Explore_Mode explore_mode = LEFT_HUGGER;
    Relative maneuver_dir = FORWARD;
    int show_hidden = 1;
    int show_path   = 1;
    int in_maneuver = 0;
    int control  = 'p';
    int paused   = 1;
    int step     = 0;
    int visited  = 0;
    int finished = 0;
    Direct direction = NORTH;
    int total = maze->width * maze->height;
    init_vars(maze, mouseMaze, &ffMap, &path, &mouse_pos, &next_pos, &goal_pos);
    init_display();

    // Add starting walls
    update_walls(maze, mouseMaze, mouse_pos, direction);

    // TODO: DELETE THESE
    Directions directions;
    clear_directions(&directions);
    get_direction(&directions);

    // Primary loop and logic to explore maze.
    // Goal is to completely populate the mouse's map,
    // or in other words to explore every block.
    while(control != 'q') {

        // Process keyboard input if any
        if(kbhit()) {
            control = getch();

            switch(control) {
            // Toggle pause / play
            case 'p':
                paused = !paused;
                step = 0;
                break;
            // Restart simulation
            case 'r':
                step      = 0;
                paused    = 1;
                visited   = 0;
                finished  = 0;
                direction = NORTH;
                total = maze->width * maze->height;
                init_vars(
                    maze, 
                    mouseMaze, 
                    &ffMap, 
                    &path, 
                    &mouse_pos, 
                    &next_pos, 
                    &goal_pos
                );
                break;
            // speed up simulation
            case 'm':
                speed += SPEED_ADJ;
                break;
            // Slow down simulation
            case 'n':
                if(speed - SPEED_ADJ > 0.5) {
                    speed -= SPEED_ADJ;
                }
                break;
            case 'z':
                explore_mode = LEFT_HUGGER;
                break;
            case 'x':
                explore_mode = FLOODFILL;
                break;
            case 'c':
                explore_mode = RIGHT_HUGGER;
                break;
            case '1':
                show_hidden = !show_hidden;
                break;
            case '2':
                show_path = !show_path;
                break;
            case 'o':
                step = 1;
                break;
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

        // Only consider exploration if not finished
        if(finished || paused) {

        // Ignore high level logic to execute maneuver
        } else if(in_maneuver) {

            Direct maneuver_abs_dir =
                relative_to_direct(direction, maneuver_dir);
            if(     maneuver_abs_dir == NORTH) mouse_pos.y++;
            else if(maneuver_abs_dir == SOUTH) mouse_pos.y--;
            else if(maneuver_abs_dir == EAST)  mouse_pos.x++;
            else if(maneuver_abs_dir == WEST)  mouse_pos.x--;
            in_maneuver = 0;
        
        // Left wall hugger logic 
        } else if(explore_mode == LEFT_HUGGER) {

            unsigned char wall_left = relative_to_wall(direction, LEFT);
            unsigned char wall_forw = relative_to_wall(direction, FORWARD);

            // Case 1: No left
            if(!has_wall(mouseMaze, mouse_pos.x, mouse_pos.y, wall_left)) {
                direction = relative_to_direct(direction, LEFT); 
                in_maneuver = 1;
            }
            // Case 2: Left and front
            else if(has_wall(mouseMaze, mouse_pos.x, mouse_pos.y, wall_forw)) {
                direction = relative_to_direct(direction, RIGHT);
            }
            // Case 3: Left and no front
            else if(!has_wall(mouseMaze, mouse_pos.x, mouse_pos.y, wall_forw)) {
                move_mouse_forward(&mouse_pos, direction); 
            }

        // Right wall hugger logic
        } else if(explore_mode == RIGHT_HUGGER) {

            unsigned char wall_right = relative_to_wall(direction, RIGHT);
            unsigned char wall_forw = relative_to_wall(direction, FORWARD);

            // Case 1: No right
            if(!has_wall(mouseMaze, mouse_pos.x, mouse_pos.y, wall_right)) {
                direction = relative_to_direct(direction, RIGHT); 
                in_maneuver = 1;
            }
            // Case 2: right and front
            else if(has_wall(mouseMaze, mouse_pos.x, mouse_pos.y, wall_forw)) {
                direction = relative_to_direct(direction, LEFT);
            }
            // Case 3: right and no front
            else if(!has_wall(mouseMaze, mouse_pos.x, mouse_pos.y, wall_forw)) {
                move_mouse_forward(&mouse_pos, direction); 
            }
        // Floodfill to explore logic
        } else if(explore_mode == FLOODFILL) {

        }

        // Add walls from new coordinate
        update_walls(maze, mouseMaze, mouse_pos, direction);
            
        // Check finish conditions
        if(visited >= total) {
            finished = 1;
        }

        // Draw all structures to screen
        clear_display();
        put_posts(maze);
        if(show_hidden) put_hidden_walls(maze);
        put_visible_walls(mouseMaze); 
        if(show_path) put_path(maze, &path);
        put_mouse(maze, direction, mouse_pos);
        render();

        // Delay before next frame 
        my_sleep(speed);
    }
    finish_display();
    return exit_code;
}
