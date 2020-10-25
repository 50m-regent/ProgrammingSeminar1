#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void visualize(int board1, int board2) {
    system("clear");

    puts("-------------");
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            printf("|");
            if (board1 & (1 << (y * 3 + x))) {
                printf(" o ");
            } else if (board2 & (1 << (y * 3 + x))) {
                printf(" x ");
            } else {
                printf(" %d ", y * 3 + x + 1);
            }
        }
        puts("|\n-------------");
    }
}

int main () {
    srand((unsigned)time(NULL));

    int board1 = 0, board2 = 0, target, turn = 0;

    while (++turn < 10) {
        visualize(board1, board2);

        do {
            printf("Player%d Target<< ", turn % 2 ? 1 : 2);
            scanf("%d", &target);
            target--;
        } while (
            target < 0 || target > 8 ||
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