#ifndef _CONST_H_
#define _CONST_H_

#define WIDTH 8  // 盤面の幅
#define HEIGHT 8 // 盤面の高さ

#define LMASK 0xfefefefefefefefeul // 盤面左マスク
#define RMASK 0x7f7f7f7f7f7f7f7ful // 盤面右マスク
#define HMASK LMASK & RMASK        // 盤面左右マスク
#define TMASK 0xffffffffffffff00ul // 盤面上マスク
#define BMASK 0x00fffffffffffffful // 盤面下マスク
#define VMASK TMASK & BMASK        // 盤面上下マスク

typedef unsigned long long bitboard; // ビットボード

// 探索する方向(八近傍)
static const int directions[] = {
    1,
    -1,
    WIDTH,
    -WIDTH,
    WIDTH - 1,
    -WIDTH + 1,
    WIDTH + 1,
    -WIDTH - 1
};

// directionsのそれぞれの要素の方向のマスク
static const bitboard masks[] = {
    RMASK,
    LMASK,
    BMASK,
    TMASK,
    LMASK & BMASK,
    RMASK & TMASK,
    RMASK & BMASK,
    LMASK & TMASK
};

// 各盤面のスコア
static const int scores[] = {
    50,
    -1,
    -3,
    -12,
    -15
};

// それぞれのスコアがどのマスに割り振られているか
static const bitboard score_masks[] = {
    0x8100000000000081ul,
    0x180018bdbd180018ul,
    0x003c424242423c00ul,
    0x4281000000008142ul,
    0x0042000000004200ul
};

#endif