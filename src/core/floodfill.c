/**
 * File:
 *     floodfill.c
 *
 * Description:
 *     Implementation for floodfill.h.
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
#include "micromouse/core/floodfill.h"


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
Coord peek_q(Queue* queue) {
    return queue->array[queue->head];
}

/*
 * If there is space on the queue, move the tail
 * back one element and add the Coord to the tail.
 */
unsigned push_back_q(Queue* queue, const Coord* coord) {

    // Guard
    if(queue->size >= queue->cap) {
        return false;
    }

    if(queue->size != 0) {
        queue->tail = (queue->tail + 1) % queue->cap;
    }
    queue->array[queue->tail] = *coord;
    queue->size++;
    return true;
}

/* 
 * Moves the head up by one.
 */
unsigned pop_front_q(Queue* queue) {

    if(queue->size != 0) {
        queue->size--;
        if(queue->head != queue->tail) {
            queue->head = (queue->head + 1) % queue->cap;
        }
        return true;
    }
    else {
        return false;
    }
}

/////////////////////////////////////////////////////


unsigned floodfill(
    FloodObj* floodObj,
    const Maze* maze,
    const Coord* target
) {
    
    Coord curr_node;
    Coord temp_node;
    Queue open_nodes;

    // BFS depth trackers 
    unsigned char depth = 0;
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
    push_back_q(&open_nodes, target);
    visited[target->x][target->y] = 1;

    // While the queue is not empty, process nodes
    while(open_nodes.size > 0) {

        // Generate floodfill data from top node
        curr_node = peek_q(&open_nodes);
        pop_front_q(&open_nodes);
        floodObj->map[curr_node.x][curr_node.y] = depth;  

        // Add surrounding unexplored nodes to queue
        // NORTH CASE
        if(!has_field(maze, curr_node.x, curr_node.y, WALL_NORTH) &&
           visited[curr_node.x][curr_node.y + 1] == 0) {

            temp_node.x = curr_node.x;
            temp_node.y = curr_node.y + 1;
            visited[temp_node.x][temp_node.y] = 1;
            push_back_q(&open_nodes, &temp_node);
        }
        // SOUTH CASE
        if(!has_field(maze, curr_node.x, curr_node.y, WALL_SOUTH) &&
           visited[curr_node.x][curr_node.y - 1] == 0) {

            temp_node.x = curr_node.x;
            temp_node.y = curr_node.y - 1;
            visited[temp_node.x][temp_node.y] = 1;
            push_back_q(&open_nodes, &temp_node);
        }
        // EAST CASE
        if(!has_field(maze, curr_node.x, curr_node.y, WALL_EAST) &&
           visited[curr_node.x + 1][curr_node.y] == 0) {

            temp_node.x = curr_node.x + 1;
            temp_node.y = curr_node.y;
            visited[temp_node.x][temp_node.y] = 1;
            push_back_q(&open_nodes, &temp_node);
        }
        // WEST CASE
        if(!has_field(maze, curr_node.x, curr_node.y, WALL_WEST) &&
           visited[curr_node.x - 1][curr_node.y] == 0) {

            temp_node.x = curr_node.x - 1;
            temp_node.y = curr_node.y;
            visited[temp_node.x][temp_node.y] = 1;
            push_back_q(&open_nodes, &temp_node);
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
            return false;
        }
    }
    return true;
}