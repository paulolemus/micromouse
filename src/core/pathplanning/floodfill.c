/*
 * File     : floodfill.c
 * Author   : Paulo Lemus
 * Created  : 9/22/2017
 */

#include <micromouse/config.h>
#include <micromouse/core/pathplanning/floodfill.h>
#include <micromouse/core/pathplanning/directions.h>
#include <micromouse/core/pathplanning/coord.h>
#include <micromouse/core/pathplanning/path.h>
#include <micromouse/core/maze/maze.h>

/////////////////////////////////////////////////////
/**
 * Queue data structure required for floodfill algorithm.
 * Queue implemented as a wrap-around array.
 */
typedef struct Queue {
    unsigned cap;
    unsigned head;
    unsigned tail;
    unsigned size;
    Coord array[MAX_WIDTH * MAX_HEIGHT];
} Queue;

/*
 * Initialize values of queue to default state
 */
void init_queue(Queue* queue) {
    queue->cap = MAX_WIDTH * MAX_HEIGHT;
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}

/* Get the Coord in the front of the queue.
 */
Coord peek(Queue* queue) {
    return queue->array[queue->head];
}

/*
 * If there is space on the queue, move the tail
 * back one element and add the Coord to the tail.
 */
unsigned enqueue(Queue* queue, const Coord* coord) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;

    if(queue->size < queue->cap) {
        if(queue->size != 0) {
            queue->tail = (queue->tail + 1) % queue->cap;
        }
        queue->array[queue->tail] = *coord;
        queue->size++;
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

/* 
 * Moves the head up by one.
 */
unsigned dequeue(Queue* queue) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;

    if(queue->size != 0) {
        queue->size--;
        if(queue->head != queue->tail) {
            queue->head = (queue->head + 1) % queue->cap;
        }
        return SUCCESS;
    }
    else {
        return FAILURE;
    }
}


/////////////////////////////////////////////////////

unsigned floodfill(
    FloodObj* floodObj,
    const Maze* maze,
    const Coord* goal_pos
) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;
    
    // Coordinate of current node
    Coord curr_node;
    Coord temp_node;
    // Queue to hold open nodes
    Queue open_nodes;
    // BFS depth trackers 
    unsigned char depth         = 0;
    unsigned nodes_til_increase = 1;
    // Infinite loop protection
    unsigned loop_count = 0;
    unsigned loop_limit = MAX_WIDTH * MAX_HEIGHT;

    // Matrix representing visited indicies
    unsigned char visited[maze->width][maze->height];
    
    // Data structure initializations
    unsigned i, j;
    for(i = 0; i != maze->width; ++i) {
        for(j = 0; j != maze->height; ++j) {
            visited[i][j] = 0;
        }
    }
    init_queue(&open_nodes);
    
    // Add the goal node to the open queue to begin.
    enqueue(&open_nodes, goal_pos);
    visited[goal_pos->x][goal_pos->y] = 1;

    // While the queue is not empty, process nodes
    while(open_nodes.size > 0) {

        // Generate floodfill data from top node
        curr_node = peek(&open_nodes);
        dequeue(&open_nodes);
        floodObj->map[curr_node.x][curr_node.y] = depth;  

        // Add surrounding unexplored nodes to queue
        // NORTH CASE
        if(!has_wall(maze, curr_node.x, curr_node.y, NORTH_WALL) &&
           visited[curr_node.x][curr_node.y + 1] == 0) {

            temp_node.x = curr_node.x;
            temp_node.y = curr_node.y + 1;
            visited[temp_node.x][temp_node.y] = 1;
            enqueue(&open_nodes, &temp_node);
        }
        // SOUTH CASE
        if(!has_wall(maze, curr_node.x, curr_node.y, SOUTH_WALL) &&
           visited[curr_node.x][curr_node.y - 1] == 0) {

            temp_node.x = curr_node.x;
            temp_node.y = curr_node.y - 1;
            visited[temp_node.x][temp_node.y] = 1;
            enqueue(&open_nodes, &temp_node);
        }
        // EAST CASE
        if(!has_wall(maze, curr_node.x, curr_node.y, EAST_WALL) &&
           visited[curr_node.x + 1][curr_node.y] == 0) {

            temp_node.x = curr_node.x + 1;
            temp_node.y = curr_node.y;
            visited[temp_node.x][temp_node.y] = 1;
            enqueue(&open_nodes, &temp_node);
        }
        // WEST CASE
        if(!has_wall(maze, curr_node.x, curr_node.y, WEST_WALL) &&
           visited[curr_node.x - 1][curr_node.y] == 0) {

            temp_node.x = curr_node.x - 1;
            temp_node.y = curr_node.y;
            visited[temp_node.x][temp_node.y] = 1;
            enqueue(&open_nodes, &temp_node);
        }

        // Logic to keep track of depth
        nodes_til_increase--;
        if(nodes_til_increase == 0) {
            depth++;
            nodes_til_increase = open_nodes.size;
        }

        // Infinite loop prevention
        loop_count++;
        if(loop_count == loop_limit) {
            return FAILURE;
        }
    }
    return SUCCESS;
}


/*
 * Warning: x and y passed in are not safety checked
 */
unsigned ff_get_path(
    const FloodObj* floodObj,
    const Maze* maze,
    const Coord* mouse_pos,
    Path* path
) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;
    unsigned loop_count = 0;
    unsigned loop_limit = MAX_WIDTH * MAX_HEIGHT;
    // Path data variables
    unsigned x_curr = mouse_pos->x;
    unsigned y_curr = mouse_pos->y;
    unsigned index  = 0;

    // Guard against invalid start coordinates
    if(x_curr >= maze->width || y_curr >= maze->height) {
        return FAILURE;
    }

    // Add self as first node in path
    path->coords[index].x = x_curr;
    path->coords[index].y = y_curr;


    // Build path until we land on a 0 indicating goal
    while(floodObj->map[x_curr][y_curr] != 0) {

        index++;
        loop_count++;

        // Calculate which adjacent open square has smallest value
        Direct direction = DIRECT_COUNT;
        unsigned char curr_val = floodObj->map[x_curr][y_curr];

        // Check north wall
        if(!has_wall(maze, x_curr, y_curr, NORTH_WALL) &&
           floodObj->map[x_curr][y_curr + 1] < curr_val) {
            direction = NORTH;
            curr_val = floodObj->map[x_curr][y_curr + 1];
        }
        // Check south wall
        if(!has_wall(maze, x_curr, y_curr, SOUTH_WALL) &&
           floodObj->map[x_curr][y_curr - 1] < curr_val) {
            direction = SOUTH;
            curr_val = floodObj->map[x_curr][y_curr - 1];
        }
        // Check east wall
        if(!has_wall(maze, x_curr, y_curr, EAST_WALL) &&
           floodObj->map[x_curr + 1][y_curr] < curr_val) {
            direction = EAST;
            curr_val = floodObj->map[x_curr + 1][y_curr];
        }
        // Check west wall
        if(!has_wall(maze, x_curr, y_curr, WEST_WALL) &&
           floodObj->map[x_curr - 1][y_curr] < curr_val) {
            direction = WEST;
            curr_val = floodObj->map[x_curr - 1][y_curr];
        }

        // Add direction to maze
        switch(direction) {
        case NORTH:
            y_curr++;
            break;
        case SOUTH:
            y_curr--;
            break;
        case EAST:
            x_curr++;
            break;
        case WEST:
            x_curr--;
            break;
        default:
            // Should not reach
            break;
        }
        path->coords[index].x = x_curr;
        path->coords[index].y = y_curr;

        // Failure conditions
        if(loop_count == loop_limit || index == PATH_SIZE) {
            return FAILURE;
        }
    }

    // Add last item from path and set path struct variables
    path->curr = 0;
    path->end  = index;
    path->coords[index].x = x_curr;
    path->coords[index].y = y_curr;
    return SUCCESS;
}


unsigned ff_get_directions(
    const FloodObj* floodObj,
    const Maze* maze,
    const Coord* mouse_pos,
    Directions* directions
) {
    const unsigned SUCCESS = 1;
    const unsigned FAILURE = 0;

    return SUCCESS;
}
