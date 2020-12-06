#include "input.h"

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

bitboard place(bitboard input, bitboard *player, bitboard *opponent) {
    int i, j;
    bitboard rev = 0, trans;
    for (i = 0; i < 8; i++) {
        trans = input;

        for (j = 0; j < WIDTH; j++) {
            trans |= *opponent & masks[i] & (directions[i] > 0 ? (trans >> directions[i]) : (trans << -directions[i]));
        }
        if ((trans | (directions[i] > 0 ? (trans >> directions[i]) : (trans << -directions[i]))) & *player & masks[i]) rev |= trans;
    }

    *player ^= rev;
    *opponent ^= rev & *opponent;

    return rev;
}

bitboard get_random_input(bitboard placeable, bitboard player, bitboard opponent) {
    bitboard input;
    do {
        input = coord2bit(
            rand() % WIDTH,
            rand() % HEIGHT
        );
    } while(!(placeable & input));

    return input;
}

int eval(bitboard placeable, bitboard player, bitboard opponent) {
    int bp = 0, cn, i;
    for (i = 0; i < 5; i++) {
        bp += scores[i] * (standing_bit(player & score_masks[i]) - standing_bit(opponent & score_masks[i]));
    }

    cn = -standing_bit(placeable);

    if (standing_bit(~(player | opponent)) < 12) {
        return standing_bit(player) - standing_bit(opponent);
    } else if (standing_bit(~(player | opponent)) < 30) {
        return bp;
    } else if (standing_bit(~(player | opponent)) < 40) {
        return 2 * bp + cn;
    } else {
        return 2 * bp + 3 * cn;
    }
}

int negamax(bitboard now, bitboard player, bitboard opponent, int depth, int a, int b) {
    int x, y, score;
    bitboard placeable;

    place(now, &player, &opponent);
    placeable = scout(player, opponent);

    if (!placeable) {
        if (standing_bit(~(player | opponent)) == 0) {
            return eval(placeable, player, opponent);
        } else {
            return -100;
        }
    }

    if (!depth) {
        return eval(placeable, player, opponent);
    }

    for (y = 0; y < HEIGHT && a < b; y++) {
        for (x = 0; x < WIDTH && a < b; x++) {
            if (placeable & coord2bit(x, y)) {
                score = -negamax(coord2bit(x, y), opponent, player, depth - 1, -b, -a);
                if (a < score) a = score;
            }
        }
    }

    return score;
}

bitboard get_negamax_input(bitboard placeable, bitboard player, bitboard opponent) {
    int x, y, mx = -1e8, score;
    bitboard now, ret = 0;

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (placeable & (now = coord2bit(x, y))) {
                score = negamax(now, player, opponent, 1, -1e8, 1e8);

                if (score > mx) {
                    mx = score;
                    ret = now;
                }
            }
        }
    }
    return ret;
}

bitboard get_human_input(bitboard placeable, bitboard player, bitboard opponent) {
    bitboard input;
    int is_first = 1;
    char c, d, e;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (placeable & coord2bit(x, y)) {
                printf("%c%d: %d\n", 'A' + x, y + 1, negamax(coord2bit(x, y), player, opponent, 1, -1e8, 1e8));
            }
        }
    }
    puts("");

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