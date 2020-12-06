#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "const.h"
#include "bitboard.h"

bitboard scout(bitboard player, bitboard opponent);
bitboard place(bitboard input, bitboard *player, bitboard *opponent);
bitboard get_random_input(bitboard placeable, bitboard player, bitboard opponent);
int eval(bitboard placeable, bitboard player, bitboard opponent);
int negamax(bitboard now, bitboard player, bitboard opponent, int depth, int a, int b);
bitboard get_negamax_input(bitboard placeable, bitboard player, bitboard opponent);
bitboard get_human_input(bitboard placeable, bitboard player, bitboard oppoenent);

#endif