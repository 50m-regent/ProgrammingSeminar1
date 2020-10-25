#ifndef GAME
#define GAME

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "board.h"

// search for placeable cells
char **scout(
    char **board,
    int board_width,
    int board_height,
    int *placeable_cnt,
    int turn
);

// calculate and print score
int print_score(
    char **board,
    int board_width,
    int board_height
);

// run game
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