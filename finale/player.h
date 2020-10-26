#ifndef PLAYER
#define PLAYER

#include <stdio.h>
#include "board.h"

// get human input
void get_human_input(
    Board board, // board
    char** placeable, // placeable map
    int *x, // x input
    int *y // y input
);

#endif