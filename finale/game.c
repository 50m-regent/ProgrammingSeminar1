#include "game.h"

char **scout(char **board, int board_width, int board_height, int *placeable_cnt, int turn) {
    int x, y;
    char **placeable = malloc(board_height * sizeof(char*));
    for (y = 0; y < board_height; y++) {
        placeable[y] = malloc(board_width * sizeof(char));
    }

    *placeable_cnt = 0;

    return placeable;
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
        placeable_cnt;

    char **placeable;

    while (2 > pass_cnt) {
        placeable = scout(board, board_width, board_height, &placeable_cnt, turn = (turn + 1) % 2);

        print_board(board, placeable, board_width, board_height);
        printf("%s's turn\n", turn ? "White" : "Black");
        winner = print_score(board, board_width, board_height);

        if (0 == placeable_cnt) {
            pass_cnt++;
            puts("Pass");
            sleep(1);
        } else {
            pass_cnt = 0;
        }
    }

    free_board(placeable, board_height);

    return winner;
}

void endroll(char** board, int board_width, int board_height) {
    int tmp;
    print_board(board, scout(board, board_width, board_height, &tmp, 0), board_width, board_height);
    puts("Game Finished!");

    int winner = print_score(board, board_width, board_height);
    if (0 == winner) {
        puts("Draw");
    } else {
        printf("Winner: %s!\n", (1 == winner) ? "Black" : "White");
    }

    free_board(board, board_height);
}