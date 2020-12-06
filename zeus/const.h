#ifndef _CONST_H_
#define _CONST_H_

#define WIDTH 8
#define HEIGHT 8

#define LMASK 0xfefefefefefefefeul
#define RMASK 0x7f7f7f7f7f7f7f7ful
#define HMASK LMASK & RMASK
#define TMASK 0xffffffffffffff00ul
#define BMASK 0x00fffffffffffffful
#define VMASK TMASK & BMASK

typedef unsigned long long bitboard;

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

static const int scores[] = {
    50,
    -1,
    -3,
    -12,
    -15
};

static const bitboard score_masks[] = {
    0x8100000000000081ul,
    0x180018bdbd180018ul,
    0x003c424242423c00ul,
    0x4281000000008142ul,
    0x0042000000004200ul
};

#endif