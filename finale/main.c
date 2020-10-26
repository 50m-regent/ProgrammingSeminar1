#include "header.h"

#define FILE_PATH "./data.csv"

int main() {
    int
        board_width,
        board_height;

    Board board;
    if (-2 == (board.board = load_board(FILE_PATH, &board))[0][0]) {
        return EXIT_FAILURE;
    }

    // board = restore("./record.txt", &board_width, &board_height);

    play_game(&board);
    endroll(&board);

    return EXIT_SUCCESS;
}