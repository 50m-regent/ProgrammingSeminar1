#include "header.h"

void endroll(char** board, int board_width, int board_height) {
    print_board(board, board_width, board_height);
    puts("Game Finished!");

    int winner = print_score(board, board_width, board_height);
    if (0 == winner) {
        puts("Draw");
    } else {
        printf("Winner: %s!\n", (1 == winner) ? "Black" : "White");
    }

    free_board(board, board_height);
}

int main() {
    int
        board_width,
        board_height;

    char **board;
    if (-2 == (board = get_board("./data.csv", &board_width, &board_height))[0][0]) {
        return EXIT_FAILURE;
    }

    play_game(board, board_width, board_height);
    endroll(board, board_width, board_height);

    return EXIT_SUCCESS;
}