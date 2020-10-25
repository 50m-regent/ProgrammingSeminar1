#include "game.h"

int scout(char **board, int board_width, int board_height, int turn) {
    return 0;
}

int print_score(char **board, int board_width, int board_height) {
    int x, y, black = 0, white = 0;
    for (y = 0; y < board_height; y++) {
        for (x = 0; x < board_width; x++) {
            if (1 == board[y][x]) {
                black++;
            } else if (-1 == board[y][x]) {
                white++;
            }
        }
    }

    printf("Black %d : %d White\n", black, white);

    return (black > white) ? 1 : ((black < white) ? -1 : 0);
}

int play_game(char **board, int board_width, int board_height) {
    int
        turn = 1,
        pass_cnt = 0,
        winner,
        placable_cnt;

    while (2 > pass_cnt) {
        placable_cnt = scout(board, board_width, board_height, turn = (turn + 1) % 2);

        print_board(board, board_width, board_height);
        printf("%s's turn\n", turn ? "White" : "Black");
        winner = print_score(board, board_width, board_height);

        if (0 == placable_cnt) {
            pass_cnt++;
            puts("Pass");
            sleep(1);
        } else {
            pass_cnt = 0;
        }
    }

    return winner;
}