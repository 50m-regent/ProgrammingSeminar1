#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BOARD_SIZE 4

#if BOARD_SIZE < 4
    #define HLINE "----"
    #define CIRCLE " o "
    #define CROSS " x "
    #define NUM " %d "
#else
    #define HLINE "-----"
    #define CIRCLE "  o "
    #define CROSS "  x "
    #define NUM " %2d "
#endif

void visualize(int board1, int board2) {
    system("clear");

    for (int x = 0; x < BOARD_SIZE; x++) {
        printf(HLINE);
    }
    puts("-");

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            printf("|");
            if (board1 & (1 << (y * BOARD_SIZE + x))) {
                printf(CIRCLE);
            } else if (board2 & (1 << (y * BOARD_SIZE + x))) {
                printf(CROSS);
            } else {
                printf(NUM, y * BOARD_SIZE + x + 1);
            }
        }

        puts("|");
        for (int x = 0; x < BOARD_SIZE; x++) {
            printf(HLINE);
        }
        puts("-");
    }
}

int main () {
    srand((unsigned)time(NULL));

    int board1 = 0, board2 = 0, target, turn = 0;

    while (++turn <= BOARD_SIZE * BOARD_SIZE) {
        visualize(board1, board2);

        do {
            printf("Player%d Target<< ", turn % 2 ? 1 : 2);
            scanf("%d", &target);
            target--;
        } while (
            target < 0 || target >= BOARD_SIZE * BOARD_SIZE ||
            board1 & (1 << target) ||
            board2 & (1 << target)
        );

        if (turn % 2) {
            board1 |= 1 << target;
        } else {
            board2 |= 1 << target;
        }
    }

    visualize(board1, board2);
    
    return EXIT_SUCCESS;
}