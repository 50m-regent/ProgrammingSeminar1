#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "const.h"
#include "bitboard.h"
#include "input.h"

/*--------------------------------------
盤面の表示
--------------------------------------*/
void print_board(
    bitboard black,    // 黒盤面
    bitboard white,    // 白盤面
    bitboard placeable // 着手可能マス
) {
    system("clear");
    printf("\x1b[42m"); // 背景色

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
                printf(". "); // 着手可能マス
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

/*--------------------------------------
コマ数の算出、表示

戻り値:
    黒の方が駒が多いなら1、白なら-1、コマ数が同じなら0
--------------------------------------*/
int print_score(
    bitboard black, // 黒盤面
    bitboard white, // 白盤面
    int debug // 表示を行うか否か
) {
    // 表示を行う場合
    if (debug) printf("⚫️ %d : %d ⚪️\n", standing_bit(black), standing_bit(white));

    return (standing_bit(black) > standing_bit(white)) ?
        1 : ((standing_bit(black) < standing_bit(white)) ? -1 : 0);
}

/*--------------------------------------
ゲームの実行

戻り値:
    黒が勝ったら1、白なら-1、引き分けなら0
--------------------------------------*/
int play(
    bitboard *black, // 黒盤面
    bitboard *white, // 白盤面
    int debug,       // 情報の表示をするか否か
    bitboard (*player1)( // 黒の入力関数
        bitboard placeable,
        bitboard player,
        bitboard opponent
    ),
    bitboard (*player2)( // 白の入力関数
        bitboard placeable,
        bitboard player,
        bitboard opponent
    )
) {
    int
        pass_cnt = 0, // 何回連続パスが行われたか
        turn = 0,     // 手番 (黒番なら0、白なら1)
        winner;       // 勝者 (毎番コマの多い方を保持)
    bitboard
        placeable, // 着手可能マス
        input,     // 入力
        victim;    // ひっくり返されたコマ (Undo処理をするために保持しているが未実装)

    // 試合終了(パスが二回連続行われない間)までループ
    while (2 > pass_cnt) {
        // 着手可能マスを求める
        placeable = (0 == turn) ? scout(*black, *white) : scout(*white, *black);

        // 盤面表示
        if (debug) print_board(*black, *white, placeable);
        // コマ数計算
        winner = print_score(*black, *white, debug);
        // 手番表示
        if (debug) printf("%s's turn\n", turn ? "⚪️" : "⚫️");

        // パス処理
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

        // 手の入力
        input = turn ? player2(placeable, *white, *black) : player1(placeable, *black, *white);

        // コマの設置処理
        if (turn) {
            victim = place(input, white, black);
        } else {
            victim = place(input, black, white);
        }

        // 手番交代
        turn = (turn + 1) % 2;
    }

    return winner;
}

/*--------------------------------------
盤面の初期化
--------------------------------------*/
void board_init(
    bitboard *black, // 黒盤面
    bitboard *white  // 白盤面
) {
    *black = coord2bit(WIDTH / 2, HEIGHT / 2 - 1) | coord2bit(WIDTH / 2 - 1, HEIGHT / 2);
    *white = coord2bit(WIDTH / 2 - 1, HEIGHT / 2 - 1) | coord2bit(WIDTH / 2, HEIGHT / 2);
}

/*--------------------------------------
ある程度の試合数を行って一人目の勝率を求める
--------------------------------------*/
void verify(
    int epoch, // 試合数
    bitboard (*player1)( // 一人目の入力
        bitboard placeable,
        bitboard player,
        bitboard opponent
    ),
    bitboard (*player2)( // 二人目の入力
        bitboard placeable,
        bitboard player,
        bitboard opponent
    )
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

    // 黒番白番交代
    for (int i = 0; i < epoch; i++) {
        board_init(&black, &white);
        if (play(&black, &white, 0, player2, player1) < 0) wsum++;
        print_board(black, white, 0);
        printf("Game%d\n", i + 1);
        print_score(black, white, 1);
    }

    // 黒番勝率
    printf("As black winrate: %lf\n", (double)bsum / epoch);
    // 白番勝率
    printf("As white winrate: %lf\n", (double)wsum / epoch);
}

int main() {
    srand((unsigned)time(NULL));

    bitboard black, white;
    board_init(&black, &white);
    play(&black, &white, 1, get_human_input, get_human_input);
    
    return EXIT_SUCCESS;
}