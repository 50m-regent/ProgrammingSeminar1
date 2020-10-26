#include "game.h"

void flip(Board* board, int x, int y, int dx, int dy, int turn) {
    while (
        board->board[y][x] != (turn ? 1 : -1) &&
        x >= 0 && x < board->width &&
        y >= 0 && y < board->height
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

int print_score(Board board) {
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

    printf("Black %d : %d White\n", black, white);

    return (black > white) ? 1 : ((black < white) ? -1 : 0);
}

int play_game(Board *board) {
    int
        x, y,
        turn = 0,
        pass_cnt = 0,
        winner,
        placeable_cnt;

    char **placeable;
    char record[RECORD_LEN] = "";

    while (2 > pass_cnt) {
        placeable = scout(*board, &placeable_cnt, turn = (turn + 1) % 2);

        print_board(*board, placeable);
        winner = print_score(*board);
        printf("%s's turn\n", turn ? "Black" : "White");

        if (0 == placeable_cnt) {
            pass_cnt++;
            puts("Pass");
            sleep(1);
            continue;
        } else {
            pass_cnt = 0;
        }

        get_human_input(*board, placeable, &x, &y);
        place(board, x, y, turn);
        sprintf(record, "%s%c%d", record, x + (turn ? 'A' : 'a'), y + 1);
        save_record(RECORD_PATH, record, *board);
        save_board(SAVE_PATH, *board);
    }

    return winner;
}

void endroll(Board *board) {
    int tmp;
    print_board(*board, scout(*board, &tmp, 0));
    puts("Game Finished!");

    int winner = print_score(*board);
    if (0 == winner) {
        puts("Draw");
    } else {
        printf("Winner: %s!\n", (1 == winner) ? "Black" : "White");
    }

    free_board(board);
}