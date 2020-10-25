#ifndef PLAYER
#define PLAYER

#include <stdio.h>

// get human input
void get_human_input(
    char** board,
    char** placeable,
    int board_width,
    int board_height,
    int *x,
    int *y
);

#endif