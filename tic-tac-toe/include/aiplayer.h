/*
The MIT License (MIT)

Copyright (c) Swagato Chatterjee

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "board.h"
#include "vector.h"
#include <stdbool.h>

#pragma once
#ifndef AI_PLAYER_H
#define AIPLAYER_H
typedef struct aiplayer {
    board* brd;
    sdstate mseed, oseed;
} aiplayer;

typedef struct aimove{
    int score, pos;
} aimove;

/*
 * To construct an AI player:
 * 1. Construct an instance (of its subclass) with the game Board
 * 2. Call setSeed() to set the computer's seed
 * 3. Call move() which returns the next move as a 1D position
 *
 * The implementation shall not modify brd->cell[][]
 * Assume that next move is available, i.e., not game-over yet.
 */

void abuild(aiplayer*, board*);
void set_seed(aiplayer*, sdstate);
int move(aiplayer*);
aimove minimax(aiplayer*, int, sdstate);
vector* gen_moves(aiplayer*);
int eval(aiplayer*);
int evalline(aiplayer*, int, int, int, int, int, int);
bool ai_has_won(aiplayer*, sdstate);
void aclean(aiplayer*);

#endif
