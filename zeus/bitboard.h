#ifndef _BITBOARD_H_
#define _BITBOARD_H_

#include <stdio.h>
#include <string.h>
#include "const.h"

bitboard coord2bit(int x, int y);
int standing_bit(bitboard x);
void print_bit(bitboard n);

#endif