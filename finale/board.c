#include "board.h"

char **get_board(const char *fname, int *board_width, int *board_height) {
    int x, y;
    char buf[81];
    FILE *fp;
    char *tp;
    char **board;

    if (NULL == (fp = fopen(fname, "r"))) {
        board[0][0] = -2;
        puts("Error: defective board file");
        return board;
    }

    fgets(buf, sizeof(buf), fp);
    *board_width  = atoi(strtok(buf, ","));
    *board_height = atoi(strtok(NULL, ","));

    board = malloc(*board_height * sizeof(char *));
    for (y = 0; y < *board_height; y++) {
        board[y] = malloc(*board_width * sizeof(char));

        if (NULL == fgets(buf, sizeof(buf), fp)) {
            board[0][0] = -2;
            puts("Error: defective board data");
            return board;
        }

        board[y][0] = atoi(strtok(buf, ","));
        for (x = 1; x < *board_width; x++) {
            if (NULL == (tp = strtok(NULL, ","))) {
                board[0][0] = -2;
                puts("Error: defective board data");
                return board;
            }

            board[y][x] = atoi(tp);
        }
    }

    fclose(fp);
    return board;
}

void print_board(char **board, int board_width, int board_height) {
    int x, y;

    system("clear");
    printf("\x1b[42m");

    printf("   ");
    for (x = 0; x < board_width; x++) {
        printf("%c  ", x + 'A');
    }
    puts("");

    for (y = 0; y < board_height; y++) {
        printf("  ");
        for (x = 0; x < board_width; x++) {
            printf("+--");
        }
        puts("+");

        printf(" %d", y + 1);
        for (x = 0; x < board_width; x++) {
            printf("|");

            if (1 == board[y][x]) {
                printf("⚫️");
            } else if (-1 == board[y][x]) {
                printf("⚪️");
            } else if (2 == board[y][x]) {
                printf("・");
            } else {
                printf("  ");
            }
        }

        puts("|");
    }

    printf("  ");
    for (x = 0; x < board_width; x++) {
        printf("+--");
    }
    puts("+");
    printf("\x1b[0m");
}

void free_board(char **board, int board_height) {
    while (board_height--) {
        free(board[board_height]);
    }
    free(board);
}