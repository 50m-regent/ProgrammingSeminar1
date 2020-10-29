#ifndef PLAYER
#define PLAYER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

// get human input
void get_human_input(
    Board board, // board
    char** placeable, // placeable map
    int *x, // x input
    int *y // y input
);

// get random input
void get_random_input(
    Board board, // board
    char** placeable, // placeable map
    int *x,
    int *y
);

// get input of the least flipping cell
void get_least_flipping_input(
    Board board,
    char** placeable,
    int *x,
    int *y
);

#endif