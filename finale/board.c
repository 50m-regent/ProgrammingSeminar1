#include "board.h"

char **get_board(const char *fname, int *board_width, int *board_height) {
    int x, y;
    char buf[81];
    FILE *fp;
    char **board;

    if (NULL == (fp = fopen(fname, "r"))) return board;

    fgets(buf, sizeof(buf), fp);
    *board_width  = atoi(strtok(buf, ","));
    *board_height = atoi(strtok(NULL, ","));

    board = malloc(*board_height * sizeof(char *));
    for (y = 0; y < *board_height; y++) {
        board[y] = malloc(*board_width * sizeof(char));

        fgets(buf, sizeof(buf), fp);
        board[y][0] = atoi(strtok(buf, ","));
        for (x = 1; x < *board_width; x++) {
            board[y][x] = atoi(strtok(NULL, ","));
        }
    }

    fclose(fp);
    return board;
}

void print_board(char **board, int board_width, int board_height) {
    int x, y;

    system("clear");
    printf("\x1b[42m");

    for (y = 0; y < board_height; y++) {
        for (x = 0; x < board_width; x++) {
            printf("---");
        }
        puts("-");

        for (x = 0; x < board_width; x++) {
            printf("|");

            if (1 == board[y][x]) {
                printf("⚫️");
            } else if (-1 == board[y][x]) {
                printf("⚪️");
            } else {
                printf("  ");
            }
        }

        puts("|");
    }

    for (x = 0; x < board_width; x++) {
        printf("---");
    }
    puts("-");
}

void free_board(char **board, int board_height) {
    while (board_height--) {
        free(board[board_height]);
    }
    free(board);
}