#include "game.h"

#define RECORD_LEN 256
#define RECORD_PATH "./record.txt"
#define SAVE_PATH "./board.csv"

void flip(char** board, int board_width, int board_height, int x, int y, int dx, int dy, int turn) {
    while (
        board[y][x] != (turn ? 1 : -1) &&
        x >= 0 && x < board_width &&
        y >= 0 && y < board_height
    ) {
        board[y][x] = (turn ? 1 : -1);
        x += dx;
        y += dy;
    }
}

void place(char **board, int board_width, int board_height, int x, int y, int turn) {
    int dx, dy;

    board[y][x] = (turn ? 1 : -1);
    for (dx = -1; 1 >= dx; dx++) {
        for (dy = -1; 1 >= dy; dy++) {
            if (dx || dy) {
                if (search(board, board_width, board_height, x + dx, y + dy, dx, dy, turn, 0)) {
                    flip(board, board_width, board_height, x + dx, y + dy, dx, dy, turn);
                }
            }
        }
    }
}

int search(char** board, int board_width, int board_height, int x, int y, int dx, int dy, int turn, int cnt) {
    if (
        x < 0 || x >= board_width ||
        y < 0 || y >= board_height
    ) {
        return 0;
    }
    if (board[y][x] == 0) {
        return 0;
    }
    if (
        (0 == turn) && (-1 == board[y][x]) ||
        (1 == turn) && (1 == board[y][x])
    ) {
        return cnt;
    }
    return search(board, board_width, board_height, x + dx, y + dy, dx, dy, turn, cnt + 1);
}

char **scout(char **board, int board_width, int board_height, int *placeable_cnt, int turn) {
    int x, y, dx, dy;
    char **placeable = malloc(board_height * sizeof(char*));
    for (y = 0; y < board_height; y++) {
        placeable[y] = malloc(board_width * sizeof(char));
        for (x = 0; x < board_width; x++) {
            placeable[y][x] = 0;
        }
    }

    *placeable_cnt = 0;
    for (y = 0; y < board_width; y++) {
        for (x = 0; x < board_height; x++) {
            if (0 == board[y][x]) {
                for (dx = -1; 1 >= dx; dx++) {
                    for (dy = -1; 1 >= dy; dy++) {
                        if (dx || dy) {
                            *placeable_cnt += placeable[y][x] += search(board, board_width, board_height, x + dx, y + dy, dx, dy, turn, 0);
                        }
                    }
                }
            }
        }
    }

    return placeable;
}

int print_score(char **board, int board_width, int board_height) {
    int x, y, black = 0, white = 0;
    for (y = 0; y < board_height; y++) {
        for (x = 0; x < board_width; x++) {
            if (1 == board[y][x]) {
                black++;
            } else if (-1 == board[y][x]) {
                white++;
            }
        }
    }

    printf("Black %d : %d White\n", black, white);

    return (black > white) ? 1 : ((black < white) ? -1 : 0);
}

int play_game(char **board, int board_width, int board_height) {
    int
        x, y,
        turn = 0,
        pass_cnt = 0,
        winner,
        placeable_cnt;

    char **placeable;
    char record[RECORD_LEN] = "";

    while (2 > pass_cnt) {
        placeable = scout(board, board_width, board_height, &placeable_cnt, turn = (turn + 1) % 2);

        print_board(board, placeable, board_width, board_height);
        winner = print_score(board, board_width, board_height);
        printf("%s's turn\n", turn ? "Black" : "White");

        if (0 == placeable_cnt) {
            pass_cnt++;
            puts("Pass");
            sleep(1);
            continue;
        } else {
            pass_cnt = 0;
        }

        get_human_input(board, placeable, board_width, board_height, &x, &y);
        place(board, board_width, board_height, x, y, turn);
        sprintf(record, "%s%c%d", record, x + (turn ? 'A' : 'a'), y + 1);
        save_record(RECORD_PATH, record);
        save_board(SAVE_PATH, board, board_width, board_height);
    }

    free_board(placeable, board_height);

    return winner;
}

void endroll(char** board, int board_width, int board_height) {
    int tmp;
    print_board(board, scout(board, board_width, board_height, &tmp, 0), board_width, board_height);
    puts("Game Finished!");

    int winner = print_score(board, board_width, board_height);
    if (0 == winner) {
        puts("Draw");
    } else {
        printf("Winner: %s!\n", (1 == winner) ? "Black" : "White");
    }

    free_board(board, board_height);
}