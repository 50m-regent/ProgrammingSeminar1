#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "const.h"
#include "bitboard.h"
#include "input.h"

void print_board(bitboard black, bitboard white, bitboard placeable) {
    system("clear");
    printf("\x1b[42m");

    printf("   ");
    for (int x = 0; x < WIDTH; x++) {
        printf("%c  ", x + 'A');
    }
    puts("");

    for (int y = 0; y < HEIGHT; y++) {
        printf("  ");
        for (int x = 0; x < WIDTH; x++) {
            printf("+--");
        }
        puts("+");

        printf(" %d", y + 1);
        for (int x = 0; x < WIDTH; x++) {
            printf("|");

            if (black >> (y * WIDTH + x) & 1) {
                printf("⚫️");
            } else if (white >> (y * WIDTH + x) & 1) {
                printf("⚪️");
            } else if (placeable >> (y * WIDTH + x) & 1) {
                printf(". ");
            } else {
                printf("  ");
            }
        }

        puts("|");
    }

    printf("  ");
    for (int x = 0; x < WIDTH; x++) {
        printf("+--");
    }
    puts("+");
    printf("\x1b[0m");
}

int print_score(bitboard black, bitboard white, int debug) {
    if (debug) printf("⚫️ %d : %d ⚪️\n", standing_bit(black), standing_bit(white));
    return (standing_bit(black) > standing_bit(white)) ?
        1 : ((standing_bit(black) < standing_bit(white)) ? -1 : 0);
}

int play(
    bitboard *black, bitboard *white,
    int debug,
    bitboard (*player1)(bitboard placeable, bitboard player, bitboard opponent),
    bitboard (*player2)(bitboard placeable, bitboard player, bitboard opponent)
) {
    int pass_cnt = 0, turn = 0, winner;
    bitboard placeable, input, victim;

    while (2 > pass_cnt) {
        placeable = (0 == turn) ? scout(*black, *white) : scout(*white, *black);

        if (debug) print_board(*black, *white, placeable);
        winner = print_score(*black, *white, debug);
        if (debug) printf("%s's turn\n", turn ? "⚪️" : "⚫️");

        if (0 == standing_bit(placeable)) {
            pass_cnt++;
            turn = (turn + 1) % 2;
            if (debug) {
                puts("Pass");
                sleep(1);
            }
            continue;
        } else {
            pass_cnt = 0;
        }

        input = turn ? player2(placeable, *white, *black) : player1(placeable, *black, *white);

        if (0 == turn) {
            victim = place(input, black, white);
        } else {
            victim = place(input, white, black);
        }

        turn = (turn + 1) % 2;
    }

    return winner;
}

void board_init(bitboard *black, bitboard *white) {
    *black = coord2bit(WIDTH / 2, HEIGHT / 2 - 1) | coord2bit(WIDTH / 2 - 1, HEIGHT / 2);
    *white = coord2bit(WIDTH / 2 - 1, HEIGHT / 2 - 1) | coord2bit(WIDTH / 2, HEIGHT / 2);
}

void verify(
    int epoch,
    bitboard (*player1)(bitboard placeable, bitboard player, bitboard opponent),
    bitboard (*player2)(bitboard placeable, bitboard player, bitboard opponent)
) {
    bitboard black, white;
    int bsum = 0, wsum = 0;

    for (int i = 0; i < epoch; i++) {
        board_init(&black, &white);
        if (play(&black, &white, 0, player1, player2) > 0) bsum++;
        print_board(black, white, 0);
        printf("Game%d\n", i + 1);
        print_score(black, white, 1);
    }

    for (int i = 0; i < epoch; i++) {
        board_init(&black, &white);
        if (play(&black, &white, 0, player2, player1) < 0) wsum++;
        print_board(black, white, 0);
        printf("Game%d\n", i + 1);
        print_score(black, white, 1);
    }

    printf("As black winrate: %lf\n", (double)bsum / epoch);
    printf("As white winrate: %lf\n", (double)wsum / epoch);
}

int main() {
    srand((unsigned)time(NULL));

    // verify(1000, get_negamax_input, get_random_input);

    for(int i = 0; i < 5; i++) {
        int t = rand();
        print_bit(t);
        printf("%d\n", standing_bit(t));
    }

    bitboard black, white;
    board_init(&black, &white);
    play(&black, &white, 1, get_human_input, get_human_input);
    
    return EXIT_SUCCESS;
}