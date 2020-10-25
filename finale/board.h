#ifndef BOARD
#define BOARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// read board and its size from csv
char **get_board(
    const char *fname,
    int *board_width,
    int *board_height
);

// print board
void print_board(
    char **board,
    char **placeable,
    int board_width,
    int board_height
);

// free board memory
void free_board(
    char **board,
    int board_height
);

#endif