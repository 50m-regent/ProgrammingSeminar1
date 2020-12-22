#include "board.h"

int save_board(const char *fname, Board board) {
    int x, y;
    FILE *fp;

    if (NULL == (fp = fopen(fname, "w+"))) {
        puts("Error: Can't open file. (save_board())");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%d, %d\n", board.width, board.height);

    for (y = 0; y < board.height; y++) {
        fprintf(fp, "%d", board.board[y][0]);
        for (x = 1; x < board.width; x++) {
            fprintf(fp, ", %d", board.board[y][x]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

int save_record(const char *fname, char *record, Board board) {
    FILE *fp;

    if (NULL == (fp = fopen(fname, "w+"))) {
        puts("Error: Can't open file");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%d, %d\n%s", board.width, board.height, record);

    fclose(fp);
    return EXIT_SUCCESS;
}

char **load_board(const char *fname, Board *board) {
    int x, y;
    char buf[81];
    FILE *fp;
    char *tp;
    char **board_buf;

    if (NULL == (fp = fopen(fname, "r"))) {
        board_buf[0][0] = -2;
        puts("Error: defective board file");
        return board_buf;
    }

    fgets(buf, sizeof(buf), fp);
    board->width  = atoi(strtok(buf, ","));
    board->height = atoi(strtok(NULL, ","));

    board_buf = malloc(board->height * sizeof(char *));
    for (y = 0; y < board->height; y++) {
        board_buf[y] = malloc(board->width * sizeof(char));

        if (NULL == fgets(buf, sizeof(buf), fp)) {
            board_buf[0][0] = -2;
            puts("Error: defective board data");
            fclose(fp);
            return board_buf;
        }

        board_buf[y][0] = atoi(strtok(buf, ","));
        for (x = 1; x < board->width; x++) {
            if (NULL == (tp = strtok(NULL, ","))) {
                board_buf[0][0] = -2;
                puts("Error: defective board data");
                fclose(fp);
                return board_buf;
            }

            board_buf[y][x] = atoi(tp);
        }
    }

    fclose(fp);
    return board_buf;
}

void replay(Board *board, char record[RECORD_LEN]) {
    int i, x, y, record_len = strlen(record), turn = 0;
    char **board_buf;

    board_buf = malloc(board->height * sizeof(char *));
    for (y = 0; y < board->height; y++) {
        board_buf[y] = malloc(board->width * sizeof(char));
        for (x = 0; x < board->width; x++) {
            board_buf[y][x] = 0;
        }
    }

    board_buf[board->height / 2 - 1][board->width / 2 - 1] =
    board_buf[board->height / 2][board->width / 2] = -1;
    board_buf[board->height / 2 - 1][board->width / 2] =
    board_buf[board->height / 2][board->width / 2 - 1] = 1;

    board->board = board_buf;

    for (i = 0; i < record_len; i++) {
        x = (record[i] > 'H') ? record[i] - 'a' : record[i] - 'A';
        y = record[++i] - '1';

        place(board, x, y, turn = (turn + 1) % 2);
    }
}

void restore(const char *fname, Board *board) {
    char buf[RECORD_LEN];
    FILE *fp;

    if (NULL == (fp = fopen(fname, "r"))) {
        puts("Error: defective record file");
        return;
    }

    fgets(buf, sizeof(buf), fp);
    board->width  = atoi(strtok(buf, ","));
    board->height = atoi(strtok(NULL, ","));

    fgets(buf, sizeof(buf), fp);
    fclose(fp);

    replay(board, buf);
}

void print_board(Board board, char** placeable) {
    int x, y;

    system("clear");
    printf("\x1b[42m");

    printf("   ");
    for (x = 0; x < board.width; x++) {
        printf("%c  ", x + 'A');
    }
    puts("");

    for (y = 0; y < board.height; y++) {
        printf("  ");
        for (x = 0; x < board.width; x++) {
            printf("+--");
        }
        puts("+");

        printf(" %d", y + 1);
        for (x = 0; x < board.width; x++) {
            printf("|");

            if (1 == board.board[y][x]) {
                printf("⚫️");
            } else if (-1 == board.board[y][x]) {
                printf("⚪️");
            } else if (placeable[y][x]) {
                printf("%2d", placeable[y][x]);
            } else {
                printf("  ");
            }
        }

        puts("|");
    }

    printf("  ");
    for (x = 0; x < board.width; x++) {
        printf("+--");
    }
    puts("+");
    printf("\x1b[0m");
}

void free_board(Board *board) {
    while (board->height--) {
        free(board->board[board->height]);
    }
    free(board->board);
}