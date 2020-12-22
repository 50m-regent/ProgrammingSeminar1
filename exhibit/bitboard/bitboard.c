#include "bitboard.h"

bitboard coord2bit(int x, int y) {
    // 入力座標が盤面外なら0を返す。
    if (
        x < 0 || x >= WIDTH ||
        y < 0 || y >= HEIGHT
    ) {
        printf("Error: Cell out of board. (coord2bit(%d, %d))\n", x, y);
        return 0;
    }
    else return 1lu << (y * WIDTH + x);
}

int standing_bit(bitboard x) {
    x -= (x >> 1 & 0x5555555555555555ul);
    x = (x >> 2  & 0x3333333333333333ul) + (x & 0x3333333333333333ul);
    x = ((x + (x >> 4))  & 0x0f0f0f0f0f0f0f0ful);
    x = (x * 0x0101010101010101ul) >> 56;
    return x;
}

void print_bit(bitboard n) {
    // 全マスについてループ
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // ビットが立っていない(0) or ビットが立っている(1)で出力
            printf("%llu", n >> (y * WIDTH + x) & 1);
        }
        puts("");
    }
}