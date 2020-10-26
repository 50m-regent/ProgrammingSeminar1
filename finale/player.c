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
        *x = c - 'a';
        *y = d - '1';
    } while (
        *x < 0 || *x >= board.width ||
        *y < 0 || *y >= board.height ||
        0 == placeable[*y][*x]
    );
}