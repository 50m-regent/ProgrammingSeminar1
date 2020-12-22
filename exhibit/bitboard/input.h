#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "const.h"
#include "bitboard.h"

/*--------------------------------------
コマの置けるマスを調べる。

戻り値:
    置けるマスが立っているビットボード
--------------------------------------*/
bitboard scout(
    bitboard player,  // 手番のプレイヤーの盤面
    bitboard opponent // 相手の盤面
);

/*--------------------------------------
コマを置いてひっくり返す。

戻り値:
    ひっくり返した場所
--------------------------------------*/
bitboard place(
    bitboard input,    // 置く場所
    bitboard *player,  // 手番のプレイヤーの盤面
    bitboard *opponent // 相手の盤面
);

/*--------------------------------------
置けるマスのうちランダムな場所を返す。

戻り値:
    マス
--------------------------------------*/
bitboard get_random_input(
    bitboard placeable, // 着手可能なマス
    bitboard player,    // 手番の盤面
    bitboard opponent   // 相手の盤面
);

/*--------------------------------------
手版のプレイヤーから見た盤面の評価値を算出する。

戻り値:
    評価値
--------------------------------------*/
int eval(
    bitboard placeable, // 着手可能なマス
    bitboard player,    // 手番の盤面
    bitboard opponent   // 相手の盤面
);

/*--------------------------------------
ネガマックス探索を行い、その手の評価値求める再帰関数。

戻り値:
    評価値
--------------------------------------*/
int negamax(
    bitboard now,      // 調べる手
    bitboard player,   // 手番の盤面
    bitboard opponent, // 相手の盤面
    int depth, // 探索する深さ
    int a,     // 最小評価値
    int b      // 最大評価値
);

/*--------------------------------------
ネガマックス探索を行い、最善手を探す。

戻り値:
    最善のマス
--------------------------------------*/
bitboard get_negamax_input(
    bitboard placeable, // 着手可能なマス
    bitboard player,    // 手番の盤面
    bitboard opponent   // 相手の盤面
);

/*--------------------------------------
ネガマックス探索を行い、最善手を探す。
各マスのネガマックス探索による評価値も出力する。

戻り値:
    入力されたマス
--------------------------------------*/
bitboard get_human_input(
    bitboard placeable, // 着手可能なマス
    bitboard player,    // 手番の盤面
    bitboard opponent   // 相手の盤面
);

#endif