#include "board.h"

int save_board(const char *fname, char **board, int board_width, int board_height) {
    int x, y;
    FILE *fp;

    if (NULL == (fp = fopen(fname, "w+"))) {
        puts("Error: Can't open file");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%d, %d\n", board_width, board_height);

    for (y = 0; y < board_height; y++) {
        fprintf(fp, "%d", board[y][0]);
        for (x = 1; x < board_width; x++) {
            fprintf(fp, ", %d", board[y][x]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

int save_record(const char *fname, char *record, int board_width, int board_height) {
    FILE *fp;

    if (NULL == (fp = fopen(fname, "w+"))) {
        puts("Error: Can't open file");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%d, %d\n%s", board_width, board_height, record);

    fclose(fp);
    return EXIT_SUCCESS;
}

char **load_board(const char *fname, int *board_width, int *board_height) {
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
                fclose(fp);
                return board;
            }

            board[y][x] = atoi(tp);
        }
    }

    fclose(fp);
    return board;
}

char **restore(const char *fname, int *board_width, int *board_height) {
    int x, y, turn = 0;
    char buf[RECORD_LEN], tmp[RECORD_LEN];
    FILE *fp;
    char **board;

    if (NULL == (fp = fopen(fname, "r"))) {
        board[0][0] = -2;
        puts("Error: defective record file");
        return board;
    }

    fgets(buf, sizeof(buf), fp);
    *board_width  = atoi(strtok(buf, ","));
    *board_height = atoi(strtok(NULL, ","));

    board = malloc(*board_height * sizeof(char *));
    for (y = 0; y < *board_height; y++) {
        board[y] = malloc(*board_width * sizeof(char));
        for (x = 0; x < *board_width; x++) {
            board[y][x] = 0;
        }
    }

    board[*board_height / 2 - 1][*board_width / 2 - 1] =
    board[*board_height / 2][*board_width / 2] = 1;
    board[*board_height / 2 - 1][*board_width / 2] =
    board[*board_height / 2][*board_width / 2 - 1] = -1;

    fgets(buf, sizeof(buf), fp);
    while (strlen(buf)) {
        x = (buf[0] > 'H') ? buf[0] - 'a' : buf[0] - 'A';
        y = buf[1] - '1';

        place(board, *board_width, *board_height, x, y, turn = (turn + 1) % 2);

        strncpy(tmp, buf + 2, strlen(buf) - 2);
        memset(buf, '\0', sizeof(buf));
        strcpy(buf, tmp);
        memset(tmp, '\0', sizeof(tmp));
    }

    fclose(fp);
    return board;
}

void print_board(char **board, char** placeable, int board_width, int board_height) {
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
            } else if (placeable[y][x]) {
                printf("%2d", placeable[y][x]);
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