#include "player.h"

void get_human_input(Board board, char** placeable, int *x, int *y) {
    int is_first = 1;
    char c, d, e;
    do {
        if (is_first) {
            is_first = 0;
        } else {
            puts("Defective input!");
        }
        printf("Input (ex: a1) <<");
        scanf("%c%c%c", &c, &d, &e);
        if ('u' == c) {
            *x = -1;
            return;
        } else if ('r' == c) {
            *y = -1;
            return;
        }

        *x = c - 'a';
        *y = d - '1';
    } while (
        *x < 0 || *x >= board.width ||
        *y < 0 || *y >= board.height ||
        0 == placeable[*y][*x]
    );
}

void get_random_input(Board board, char** placeable, int *x, int *y) {
    do {
        *x = rand() % board.width;
        *y = rand() % board.height;
    } while(0 == placeable[*y][*x]);
}

void get_least_flipping_input(Board board, char** placeable, int *x, int *y) {
    int nx, ny, min = 100;

    for (ny = 0; ny < board.height; ny++) {
        for (nx = 0; nx < board.width; nx++) {
            if (placeable[ny][nx] && min > placeable[ny][nx]) {
                min = placeable[ny][nx];
                *x = nx;
                *y = ny;
            }
        }
    }
}