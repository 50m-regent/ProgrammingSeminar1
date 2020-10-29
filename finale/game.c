#include "game.h"

void flip(Board* board, int x, int y, int dx, int dy, int turn) {
    while (
        x >= 0 && x < board->width &&
        y >= 0 && y < board->height &&
        board->board[y][x] != (turn ? 1 : -1)
    ) {
        board->board[y][x] = (turn ? 1 : -1);
        x += dx;
        y += dy;
    }
}

int search(Board board, int x, int y, int dx, int dy, int turn, int cnt) {
    if (
        x < 0 || x >= board.width ||
        y < 0 || y >= board.height
    ) {
        return 0;
    }
    if (0 == board.board[y][x]) {
        return 0;
    }
    if (
        (0 == turn) && (-1 == board.board[y][x]) ||
        (1 == turn) && (1 == board.board[y][x])
    ) {
        return cnt;
    }
    return search(board, x + dx, y + dy, dx, dy, turn, cnt + 1);
}

void place(Board *board, int x, int y, int turn) {
    int dx, dy;

    board->board[y][x] = (turn ? 1 : -1);
    for (dx = -1; 1 >= dx; dx++) {
        for (dy = -1; 1 >= dy; dy++) {
            if (dx || dy) {
                if (search(*board, x + dx, y + dy, dx, dy, turn, 0)) {
                    flip(board, x + dx, y + dy, dx, dy, turn);
                }
            }
        }
    }
}

char **scout(Board board, int *placeable_cnt, int turn) {
    int x, y, dx, dy;
    char **placeable = malloc(board.height * sizeof(char*));
    for (y = 0; y < board.height; y++) {
        placeable[y] = malloc(board.width * sizeof(char));
        for (x = 0; x < board.width; x++) {
            placeable[y][x] = 0;
        }
    }

    *placeable_cnt = 0;
    for (y = 0; y < board.width; y++) {
        for (x = 0; x < board.height; x++) {
            if (0 == board.board[y][x]) {
                for (dx = -1; 1 >= dx; dx++) {
                    for (dy = -1; 1 >= dy; dy++) {
                        if (dx || dy) {
                            *placeable_cnt += placeable[y][x] += search(board, x + dx, y + dy, dx, dy, turn, 0);
                        }
                    }
                }
            }
        }
    }

    return placeable;
}

int print_score(Board board, int debug) {
    int x, y, black = 0, white = 0;
    for (y = 0; y < board.height; y++) {
        for (x = 0; x < board.width; x++) {
            if (1 == board.board[y][x]) {
                black++;
            } else if (-1 == board.board[y][x]) {
                white++;
            }
        }
    }

    if (debug) printf("Black %d : %d White\n", black, white);

    return (black > white) ? 1 : ((black < white) ? -1 : 0);
}

void undo(Board *board, char *record[RECORD_LEN]) {
    int
        i, x = *record[strlen(*record) - 4] - ((*record[strlen(*record) - 4] > 'H') ? 'a' : 'A'),
        y = *record[strlen(*record) - 3] - '1';

    for (i = 0; i < 4; i++) {
        *record[strlen(*record) - 1] = '\0';
    }

    replay(board, *record);
}

int play_game(Board *board, char *history, int debug, void (*player1)(Board board, char** placeable, int *x, int *y), void (*player2)(Board board, char** placeable, int *x, int *y)) {
    int
        x, y,
        turn = 0,
        pass_cnt = 0,
        winner,
        placeable_cnt;

    char **placeable;
    char record[RECORD_LEN];

    sprintf(record, "%s", history);

    while (2 > pass_cnt) {
        placeable = scout(*board, &placeable_cnt, turn = (turn + 1) % 2);

        if (debug) print_board(*board, placeable);
        winner = print_score(*board, debug);
        if (debug) printf("%s's turn\n", turn ? "Black" : "White");

        if (0 == placeable_cnt) {
            pass_cnt++;
            if (debug) {
                puts("Pass");
                sleep(1);
            }
            continue;
        } else {
            pass_cnt = 0;
        }

        if (1 == turn) {
            player1(*board, placeable, &x, &y);
        } else {
            player2(*board, placeable, &x, &y);
        }
        if (0 > x) {
            undo(board, &record);
            continue;
        } else if (0 > y) {
        }

        place(board, x, y, turn);
        sprintf(record, "%s%c%d", record, x + (turn ? 'A' : 'a'), y + 1);
        save_record(RECORD_PATH, record, *board);
        save_board(SAVE_PATH, *board);
    }

    return winner;
}

void endroll(Board *board, int debug) {
    int tmp;
    if (debug) {
        print_board(*board, scout(*board, &tmp, 0));
        puts("Game Finished!");
    }

    int winner = print_score(*board, debug);

    if (debug) {
        if (0 == winner) {
            puts("Draw");
        } else {
            printf("Winner: %s!\n", (1 == winner) ? "Black" : "White");
        }
    }

    free_board(board);
}