/**
 * File: check-maze.c
 *
 * A testfile to check functionality of 
 * maze struct and maze functions.
 */

#include <stdlib.h>
#include <check.h>
#include <micromouse/core/maze/maze.h>

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

// Check that all bits are zero in array representing maze
START_TEST(check_maze_bits_zeroed) {

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

// Check that setBlockBitOn function works and does not affect other bits
START_TEST(check_maze_bit_on) {
    unsigned int checkx = 0;
    unsigned int checky = 0;
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT];

    // Assert all important bits are 0
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, NORTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, WEST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, VISITED),    0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, UNCERTAIN),  0);

    // Set first bit on
    setBitOn(maze, checkx, checky, NORTH_WALL);

    // Assert all bits are 0 except the NORTH_WALL bit
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, EAST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, WEST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, VISITED),    0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, UNCERTAIN),  0);

    // Set third bit on
    setBitOn(maze, checkx, checky, EAST_WALL);

    // Assert all bits are 0 except first and third
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, WEST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, VISITED),    0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, UNCERTAIN),  0);

    // Set sixth bit on
    setBitOn(maze, checkx, checky, UNCERTAIN);

    // Assert all bits are 0 except first, third, and sixth
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, NORTH_WALL), 1);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, SOUTH_WALL), 0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, EAST_WALL),  1);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, WEST_WALL),  0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, VISITED),    0);
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, UNCERTAIN),  1);
}
END_TEST

// Check that a bit that is on can be turned off
START_TEST(check_maze_bit_off) {
    unsigned int checkx = 0;
    unsigned int checky = 0;
    BLOCK maze[MAZE_WIDTH][MAZE_HEIGHT];
    clear_maze(maze);

    // Assert bit is not set
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, NORTH_WALL), 0);
    // Set the bit
    setBitOn(maze, checkx, checky, NORTH_WALL);
    // Assert bit is turned on
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, NORTH_WALL), 1);
    // Turn bit off
    setBitOff(maze, checkx, checky, NORTH_WALL);
    // Assert bit is turned off
    ck_assert_uint_eq(isBitSet(maze, checkx, checky, NORTH_WALL), 0);
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
    tcase_add_test(tc_core, check_maze_bits_zeroed);
    tcase_add_test(tc_core, check_maze_bit_on);
    tcase_add_test(tc_core, check_maze_bit_off);

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
