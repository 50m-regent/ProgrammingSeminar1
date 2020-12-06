#include "bitboard.h"

bitboard coord2bit(int x, int y) {
    if (
        x < 0 || x >= WIDTH ||
        y < 0 || y >= HEIGHT
    ) return 0;
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
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%llu", n >> (y * WIDTH + x) & 1);
        }
        puts("");
    }
}