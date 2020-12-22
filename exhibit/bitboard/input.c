#include "input.h"

bitboard scout(bitboard player, bitboard opponent) {
    bitboard
        hm = opponent & HMASK, // 水平方向のマスク
        vm = opponent & VMASK, // 垂直方向のマスク
        dm = hm & vm,          // 斜め方向(四辺全方向)のマスク
        hb = hm & (player >> 1 | player << 1),                      // 左右を見たときに置けるマスを記録
        vb = vm & (player >> WIDTH | player << WIDTH),              // 上下 〃
        db1 = dm & (player >> (WIDTH + 1) | player << (WIDTH + 1)), // 左上と右下 〃
        db2 = dm & (player >> (WIDTH - 1) | player << (WIDTH - 1)); // 右上と左下 〃

    // 各方向に対して相手のコマが連続しているかどうかを調べる
    for (int i = 0; i < WIDTH; i++) {
        hb |= hm & (hb >> 1 | hb << 1);
        vb |= vm & (vb >> WIDTH | vb << WIDTH);
        db1 |= dm & (db1 >> (WIDTH + 1) | db1 << (WIDTH + 1));
        db2 |= dm & (db2 >> (WIDTH - 1) | db2 << (WIDTH - 1));
    }

    // 相手のコマが連続しているもう1マス先にコマを置けるのでずらす
    hb = hb >> 1 | hb << 1;
    vb = vb >> WIDTH | vb << WIDTH;
    db1 = db1 >> (WIDTH + 1) | db1 << (WIDTH + 1);
    db2 = db2 >> (WIDTH - 1) | db2 << (WIDTH - 1);

    // 置けるマスのうち、空きますのみ立ったビットボードを返す
    return ~(player | opponent) & (hb | vb | db1 | db2);
}

bitboard place(bitboard input, bitboard *player, bitboard *opponent) {
    int i, j;
    bitboard
        rev = 0, // ひっくり返すマス
        trans;

    // 八方向についてひっくり返すコマを求める
    for (i = 0; i < 8; i++) {
        trans = input;

        // 盤面端まで相手の駒が連続してるか調べる
        for (j = 0; j < WIDTH; j++) {
            trans |= *opponent & masks[i] & (directions[i] > 0 ? (trans >> directions[i]) : (trans << -directions[i]));
        }
        // 1マス先に相手の駒があればその方向はひっくり返せる
        if ((trans | (directions[i] > 0 ? (trans >> directions[i]) : (trans << -directions[i]))) & *player & masks[i]) rev |= trans;
    }

    *player ^= rev; // 自分の盤面をひっくり返す
    *opponent ^= rev & *opponent; // 相手の盤面をひっくり返す

    return rev;
}

bitboard get_random_input(bitboard placeable, bitboard player, bitboard opponent) {
    bitboard input;

    // 置ける場所を選ぶまで乱択
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

    // 各マスのスコアを加算
    for (i = 0; i < 5; i++) {
        bp += scores[i] * (standing_bit(player & score_masks[i]) - standing_bit(opponent & score_masks[i]));
    }

    // 着手可能数を求める
    cn = -3 * standing_bit(placeable);

    // 最終盤
    if (standing_bit(~(player | opponent)) < 12) {
        return standing_bit(player) - standing_bit(opponent); // コマ数のみで評価
    // 終盤
    } else if (standing_bit(~(player | opponent)) < 30) {
        return bp; // 各マスのスコアのみで評価
    // 中盤
    } else if (standing_bit(~(player | opponent)) < 40) {
        return 2 * bp + cn; // 各マスのスコアに加えて着手可能数も考慮
    // 序盤
    } else {
        return 2 * bp + 3 * cn; // 着手可能数の比重大
    }
}

int negamax(bitboard now, bitboard player, bitboard opponent, int depth, int a, int b) {
    int x, y, score;
    bitboard placeable;

    // 一手進める
    place(now, &player, &opponent);
    placeable = scout(player, opponent);

    // 置ける場所がなければ
    if (!placeable) {
        // ゲーム終了なら
        if (standing_bit(~(player | opponent)) == 0) {
            return eval(placeable, player, opponent); // 最終盤面の評価
        // パスなら
        } else {
            return -100; // パスはよくなさそうなので負のスコア
        }
    }

    // ゲーム木の葉なら盤面評価値を返す
    if (!depth) {
        return eval(placeable, player, opponent);
    }

    // 全マスループ
    for (y = 0; y < HEIGHT && a < b; y++) {
        for (x = 0; x < WIDTH && a < b; x++) {
            // 着手可能なマスなら探索
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

    // 全マスループ
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            // 着手可能マスなら評価値を求めて、手を更新
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

    // 全着手可能マスについてネガマックス探索による評価値を表示
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (placeable & coord2bit(x, y)) {
                printf("%c%d: %d\n", 'A' + x, y + 1, negamax(coord2bit(x, y), player, opponent, 3, -1e8, 1e8));
            }
        }
    }
    puts("");

    // 入力受付
    do {
        if (is_first) {
            is_first = 0;
        } else {
            puts("Defective input!");
        }

        printf("Input (ex: a1) <<");
        scanf("%c%c%c", &c, &d, &e);

        input = coord2bit(c - 'a', d - '1');
    } while (!(input & placeable)); // 不正入力なら繰り返す

    return input;
}