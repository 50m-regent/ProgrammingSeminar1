#include "header.h"

int main() {
    int board_width, board_height;

    char **board = get_board("./data.csv", &board_width, &board_height);
    print_board(board, board_width, board_height);

    free_board(board, board_height);

    return EXIT_SUCCESS;
}