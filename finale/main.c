#include "header.h"

int main() {
    int board_width, board_height;

    char **board;
    if (-2 == (board = get_board("./data.csv", &board_width, &board_height))[0][0]) {
        return EXIT_FAILURE;
    }
    print_board(board, board_width, board_height);

    free_board(board, board_height);

    return EXIT_SUCCESS;
}