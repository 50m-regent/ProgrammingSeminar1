#include "header.h"

#define FILE_PATH "./data.csv"

int main() {
    srand((unsigned)time(NULL));

    int
        board_width,
        board_height;

    int cnt = 0;

    Board board;

    for (int i = 0; i < 1000; i++) {
        if (-2 == (board.board = load_board(FILE_PATH, &board))[0][0]) {
            return EXIT_FAILURE;
        }

        play_game(&board, "", 0, get_random_input, get_random_input);
        endroll(&board, 0);
    }

    return EXIT_SUCCESS;
}