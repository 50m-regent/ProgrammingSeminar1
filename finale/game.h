#ifndef GAME
#define GAME

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "board.h"

// search for placable cells
int scout(
    char **board,
    int board_width,
    int board_height,
    int turn
);

// calculate and print score
int print_score(
    char **board,
    int board_width,
    int board_height
);

// run game
// args:
//     char **board: board
//     int board_width: board width
//     int board_height: board height
// return:
//     winner (black: 1, white: -1, draw: 0)
int play_game(
    char **board,
    int board_width,
    int board_height
);

void endroll(
    char** board,
    int board_width,
    int board_height
);

#endif