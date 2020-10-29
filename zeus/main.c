#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 8
#define HEIGHT 8

#define LMASK 0xfefefefefefefefeul
#define RMASK 0x7f7f7f7f7f7f7f7ful
#define HMASK LMASK & RMASK
#define TMASK 0xffffffffffffff00ul
#define BMASK 0x00fffffffffffffful
#define VMASK TMASK & BMASK

typedef unsigned long long bitboard;

const int directions[] = {
    1,
    -1,
    WIDTH,
    -WIDTH,
    WIDTH - 1,
    -WIDTH + 1,
    WIDTH + 1,
    -WIDTH - 1
};

const bitboard masks[] = {
    RMASK,
    LMASK,
    BMASK,
    TMASK,
    LMASK & BMASK,
    LMASK & TMASK,
    RMASK & BMASK,
    RMASK & TMASK
};

bitboard coord2bit(int x, int y) {
    if (
        x < 0 || x >= WIDTH ||
        y < 0 || y >= HEIGHT
    ) return 0;
    else return 1lu << (y * WIDTH + x);
}

bitboard get_human_input(bitboard placeable) {
    bitboard input;
    int is_first = 1;
    char c, d, e;
    do {
        if (is_first) {
            is_first = 0;
        } else {
            puts("Defective input!");
        }

        printf("Input (ex: a1) <<");
        scanf("%c%c%c", &c, &d, &e);

        input = coord2bit(c - 'a', d - '1');
    } while (!(input & placeable));

    return input;
}

bitboard get_random_input(bitboard placeable) {
    bitboard input;
    do {
        input = coord2bit(
            rand() % WIDTH,
            rand() % HEIGHT
        );
    } while(!(placeable & input));

    return input;
}

int standing_bit(bitboard x) {
    x -= (x >> 1 & 0x5555555555555555ul);
    x = (x >> 2  & 0x3333333333333333ul) + (x & 0x3333333333333333ul);
    x = ((x + (x >> 4))  & 0x0f0f0f0f0f0f0f0ful);
    x = (x * 0x0101010101010101ul) >> 56;
    return x;
}

bitboard scout(bitboard player, bitboard opponent) {
    bitboard
        hm = opponent & HMASK,
        vm = opponent & VMASK,
        dw = hm & vm,
        hb = hm & (player >> 1 | player << 1),
        vb = vm & (player >> WIDTH | player << WIDTH),
        db1 = dw & (player >> (WIDTH + 1) | player << (WIDTH + 1)),
        db2 = dw & (player >> (WIDTH - 1) | player << (WIDTH - 1));

    for (int i = 0; i < 5; i++) {
        hb |= hm & (hb >> 1 | hb << 1);
        vb |= vm & (vb >> WIDTH | vb << WIDTH);
        db1 |= dw & (db1 >> (WIDTH + 1) | db1 << (WIDTH + 1));
        db2 |= dw & (db2 >> (WIDTH - 1) | db2 << (WIDTH - 1));
    }

    hb = hb >> 1 | hb << 1;
    vb = vb >> WIDTH | vb << WIDTH;
    db1 = db1 >> (WIDTH + 1) | db1 << (WIDTH + 1);
    db2 = db2 >> (WIDTH - 1) | db2 << (WIDTH - 1);

    return ~(player | opponent) & (hb | vb | db1 | db2);
}

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
    if (debug) printf("Black %d : %d White\n", standing_bit(black), standing_bit(white));
    return (standing_bit(black) > standing_bit(white)) ?
        1 : ((standing_bit(black) < standing_bit(white)) ? -1 : 0);
}

void place(bitboard input, bitboard *player, bitboard *opponent) {
    int i, j;
    bitboard rev = 0, trans;
    for (i = 0; i < 8; i++) {
        trans = input;

        for (j = 0; j < WIDTH; j++) {
            if (directions > 0) {

            }
            trans |= *opponent & masks[i] & (directions[i] > 0 ? (trans >> directions[i]) : (trans << -directions[i]));
        }
        if ((trans | (directions[i] > 0 ? (trans >> directions[i]) : (trans << -directions[i]))) & *player) rev |= trans;
    }

    *player ^= rev;
    *opponent ^= rev & *opponent;
}

int play(bitboard black, bitboard white, int debug, bitboard (*player1)(bitboard placeable), bitboard (*player2)(bitboard placeable)) {
    int pass_cnt = 0, turn = 0, winner;
    bitboard placeable, input;

    while (2 > pass_cnt) {
        placeable = (0 == turn) ? scout(black, white) : scout(white, black);

        if (debug) print_board(black, white, placeable);
        winner = print_score(black, white, debug);
        if (debug) printf("%s's turn\n", turn ? "White" : "Black");

        if (0 == standing_bit(placeable)) {
            pass_cnt++;
            if (debug) {
                puts("Pass");
                sleep(1);
            }
            continue;
        } else {
            pass_cnt = 0;
        }

        input = turn ? player2(placeable) : player1(placeable);

        if (0 == turn) {
            place(input, &black, &white);
        } else {
            place(input, &white, &black);
        }

        turn = (turn + 1) % 2;
    }

    return winner;
}

void board_init(bitboard *black, bitboard *white) {
    *black = coord2bit(WIDTH / 2, HEIGHT / 2 - 1) | coord2bit(WIDTH / 2 - 1, HEIGHT / 2);
    *white = coord2bit(WIDTH / 2 - 1, HEIGHT / 2 - 1) | coord2bit(WIDTH / 2, HEIGHT / 2);
}

int main() {
    srand((unsigned)time(NULL));

    bitboard black, white;

    for (int i = 0; i < 1000; i++) {
        board_init(&black, &white);
        play(black, white, 0, get_random_input, get_random_input);
    }

    return EXIT_SUCCESS;
}