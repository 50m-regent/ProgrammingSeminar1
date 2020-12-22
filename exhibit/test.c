#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int board[8][8] = {
    {50, -12, 0, -1, -1, 0, -12, 50},
    {-12, -15, -3, -3, -3, -3, -15, -12},
    {0, -3, 0, -1, -1, 0, -3, 0},
    {-1, -3, -1, -1, -1, -1, -3, -1},
    {-1, -3, -1, -1, -1, -1, -3, -1},
    {0, -3, 0, -1, -1, 0, -3, 0},
    {-12, -15, -3, -3, -3, -3, -15, -12},
    {50, -12, 0, -1, -1, 0, -12, 50}
};

void print_board(
    int b[8][8]
) {
    system("clear");
    printf("\x1b[42m"); // 背景色

    printf("   ");
    for (int x = 0; x < 8; x++) {
        printf(" %c  ", x + 'A');
    }
    puts("");

    for (int y = 0; y < 8; y++) {
        printf("  ");
        for (int x = 0; x < 8; x++) {
            printf("+---");
        }
        puts("+");

        printf(" %d", y + 1);
        for (int x = 0; x < 8; x++) {
            printf("|");

            printf("%3d", b[y][x]);
        }

        puts("|");
    }

    printf("  ");
    for (int x = 0; x < 8; x++) {
        printf("+---");
    }
    puts("+");
    printf("\x1b[0m");
}

int main() {
    print_board(board);
}