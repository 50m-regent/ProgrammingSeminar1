#include "header.h"

#define FILE_PATH "./data.csv"

int main() {
    int
        board_width,
        board_height;

    char **board;
    if (-2 == (board = load_board(FILE_PATH, &board_width, &board_height))[0][0]) {
        return EXIT_FAILURE;
    }

    play_game(board, board_width, board_height);
    endroll(board, board_width, board_height);

    return EXIT_SUCCESS;
}