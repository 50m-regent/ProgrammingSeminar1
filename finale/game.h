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

// flip disc in one direction
void flip(
    Board *board, // board
    int x, // starting cell
    int y,
    int dx, // direction
    int dy,
    int turn // game turn (0: Black, 1: White)
);

// search one direction if its flippable
int search(
    Board board, // board
    int x, // now
    int y,
    int dx, // direction
    int dy,
    int turn, // game turn (0: Black, 1: White)
    int cnt // count of how many discs you can flip in this direction
);
// return: number of flippable discs in this direction

// place disc
void place(
    Board *board, // board
    int x, // placing cell
    int y,
    int turn // game turn (0: Black, 1: White)
);

// search for placeable cells
char **scout(
    Board board, // board
    int *placeable_cnt, // sum of flippable discs
    int turn // game turn (0: Black, 1: White)
);
// return: placeable map

// calculate and print score
int print_score(
    Board board // board
);
// return: who has more discs
//     black: 1
//     white: -1
//     same: 0

// run game
int play_game(
    Board *board, // board
    char record[RECORD_LEN] // game record
);
// return: winner
//     black: 1
//     white: -1
//     draw: 0

// post processing
void endroll(
    Board *board // board
);

#endif