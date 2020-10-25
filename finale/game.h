#ifndef GAME
#define GAME

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "board.h"
#include "player.h"

#define RECORD_PATH "./record.txt"
#define SAVE_PATH "./board.csv"

// flip disc
void flip(
    char** board,
    int board_width,
    int board_height,
    int x,
    int y,
    int dx,
    int dy,
    int turn
);

// place disc
void place(
    char **board,
    int board_width,
    int board_height,
    int x,
    int y,
    int turn
);

// search one direction
int search(
    char** board,
    int board_width,
    int board_height,
    int x,
    int y,
    int dx,
    int dy,
    int turn,
    int cnt
);

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