#ifndef BOARD
#define BOARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// read board and its size from csv
// args:
//     const char *fname: file name
//     int *board_width: board width
//     int *board_height: board_height
// return:
//     success: board
//     failure: board[0][0] == -2
char **get_board(
    const char *fname,
    int *board_width,
    int *board_height
);

// print board
// args:
//     char **board: board
void print_board(
    char **board,
    int board_width,
    int board_height
);

// free board memory
// args:
//     char **board: board
//     int board_height
void free_board(
    char **board,
    int board_height
);

#endif