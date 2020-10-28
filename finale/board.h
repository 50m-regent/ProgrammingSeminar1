#ifndef BOARD
#define BOARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECORD_LEN 256

typedef struct {
    char** board; // board
    int
        width, // board width
        height; // board height
} Board;

#include "game.h"

// save board to csv
int save_board(
    const char *fname, // file name
    Board board // board
);
// return:
//     success: 1
//     fail : 0

// save record to txt
int save_record(
    const char *fname, // file name
    char *record, // game record
    Board board // board
);
// return:
//     success: 1
//     fail : 0

// read board and its size from csv
char **load_board(
    const char *fname, // file name
    Board *board // board
);
// return: loaded board

// load board from record
char **restore(
    const char *fname, // file name
    Board *board
);
// return: loaded board

// print board
void print_board(
    Board board, // board
    char **placeable // map with placeable cells
);

// free board memory
void free_board(
    Board *board // board
);

#endif