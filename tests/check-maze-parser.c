/**
 * File: check-maze-parser.c
 *
 * A testfile to check functionality of 
 * maze struct and maze functions.
 */

#include <stdlib.h>
#include <check.h>
#include <micromouse/core/maze/maze.h>
#include <micromouse/core/maze/parser.h>

// Test to ensure check works
START_TEST(check_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

// Check that all values are defined corectly
START_TEST(check_maze_definitions) {
    ck_assert_uint_eq(NORTH_WALL,   1);
    ck_assert_uint_eq(SOUTH_WALL,   2);
    ck_assert_uint_eq(EAST_WALL,    4);
    ck_assert_uint_eq(WEST_WALL,    8);
    ck_assert_uint_eq(VISITED,     16);
    ck_assert_uint_eq(UNCERTAIN,   32);
    ck_assert_uint_eq(NORTH_WALL_IDX, 0);
    ck_assert_uint_eq(SOUTH_WALL_IDX, 1);
    ck_assert_uint_eq(EAST_WALL_IDX,  2);
    ck_assert_uint_eq(WEST_WALL_IDX,  3);
    ck_assert_uint_eq(VISITED_IDX,    4);
    ck_assert_uint_eq(UNCERTAIN_IDX,  5);
}
END_TEST

// Check that maze default contruction works
START_TEST(check_maze_created) {
    
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT];
    clear_maze(maze);

    for(unsigned int x = 0; x < MAZE_WIDTH; ++x) {
        for(unsigned int y = 0; y < MAZE_HEIGHT; ++y) {
            ck_assert_uint_eq(isBitSet(maze, x, y, NORTH_WALL), 0); 
            ck_assert_uint_eq(isBitSet(maze, x, y, SOUTH_WALL), 0); 
            ck_assert_uint_eq(isBitSet(maze, x, y, EAST_WALL),  0); 
            ck_assert_uint_eq(isBitSet(maze, x, y, WEST_WALL),  0); 
            ck_assert_uint_eq(isBitSet(maze, x, y, VISITED),    0); 
            ck_assert_uint_eq(isBitSet(maze, x, y, UNCERTAIN),  0); 
        }
    }
}
END_TEST

// Ensure that empty string as argument returns NULL 
START_TEST(check_maze_parser_empty_string) {

    unsigned int width, height;
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT];
    clear_maze(maze);

    ck_assert_uint_eq(parse_maze(maze, &width, &height, ""), 0);
}
END_TEST

// Ensure invalid file returns NULL
START_TEST(check_maze_parser_invalid_filename) {

    unsigned int width, height;
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT];
    clear_maze(maze);

    ck_assert_uint_eq(parse_maze(maze, &width, &height, "SuprIlidfleNaM123.dt"), 0);
}
END_TEST

START_TEST(check_maze_parser_simple_map) {

    unsigned int width, height;
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT];
    clear_maze(maze);

    ck_assert_uint_eq(
        parse_maze(maze, &width, &height, "./maps/simple_map.data"), 
        1
    );

    ck_assert_uint_eq(width,  4);
    ck_assert_uint_eq(height, 4);
    
    // Assert correct bits are set
    ck_assert_uint_eq(isBitSet(maze, 0, 0, NORTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 0, 0, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 0, 0, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, 0, 0, WEST_WALL),  1);

    ck_assert_uint_eq(isBitSet(maze, 0, 1, NORTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 0, 1, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 0, 1, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 0, 1, WEST_WALL),  1);

    ck_assert_uint_eq(isBitSet(maze, 0, 2, NORTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 0, 2, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 0, 2, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, 0, 2, WEST_WALL),  1);

    ck_assert_uint_eq(isBitSet(maze, 0, 3, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 0, 3, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 0, 3, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 0, 3, WEST_WALL),  1);

    ck_assert_uint_eq(isBitSet(maze, 1, 0, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 1, 0, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 1, 0, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 1, 0, WEST_WALL),  1);

    ck_assert_uint_eq(isBitSet(maze, 1, 1, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 1, 1, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 1, 1, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 1, 1, WEST_WALL),  0);

    ck_assert_uint_eq(isBitSet(maze, 1, 2, NORTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 1, 2, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 1, 2, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 1, 2, WEST_WALL),  1);

    ck_assert_uint_eq(isBitSet(maze, 1, 3, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 1, 3, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 1, 3, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 1, 3, WEST_WALL),  0);

    ck_assert_uint_eq(isBitSet(maze, 2, 0, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 2, 0, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 2, 0, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 2, 0, WEST_WALL),  0);

    ck_assert_uint_eq(isBitSet(maze, 2, 1, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 2, 1, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 2, 1, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 2, 1, WEST_WALL),  0);

    ck_assert_uint_eq(isBitSet(maze, 2, 2, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 2, 2, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 2, 2, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, 2, 2, WEST_WALL),  0);

    ck_assert_uint_eq(isBitSet(maze, 2, 3, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 2, 3, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 2, 3, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, 2, 3, WEST_WALL),  0);
    
    ck_assert_uint_eq(isBitSet(maze, 3, 0, NORTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 3, 0, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 3, 0, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, 3, 0, WEST_WALL),  0);

    ck_assert_uint_eq(isBitSet(maze, 3, 1, NORTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 3, 1, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 3, 1, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, 3, 1, WEST_WALL),  0);

    ck_assert_uint_eq(isBitSet(maze, 3, 2, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 3, 2, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, 3, 2, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, 3, 2, WEST_WALL),  1);

    ck_assert_uint_eq(isBitSet(maze, 3, 3, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 3, 3, SOUTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, 3, 3, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, 3, 3, WEST_WALL),  0);
}
END_TEST

/** 
 * Function to create a test suite and add tests to it.
 */
Suite* maze_suite(void) {
    Suite* s;
    TCase* tc_core;
    s = suite_create("Maze");
    tc_core = tcase_create("Core");

    /*
     * Add tests here
     */
    tcase_add_test(tc_core, check_basic);
    tcase_add_test(tc_core, check_maze_definitions);
    tcase_add_test(tc_core, check_maze_created);
    tcase_add_test(tc_core, check_maze_parser_empty_string);
    tcase_add_test(tc_core, check_maze_parser_invalid_filename);
    tcase_add_test(tc_core, check_maze_parser_simple_map);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {

    int number_failed;
    Suite* s;
    SRunner* sr;

    s = maze_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
