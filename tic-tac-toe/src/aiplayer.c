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

#include <limits.h>
#include <stdlib.h>
#include "../include/aiplayer.h"

/* Constructor with the given game board */
void abuild(aiplayer* ai, board* brd){
    ai->brd = brd;
}

/* Set/change the seed used by computer and opponent */
void set_seed(aiplayer* ai, sdstate seed){
    ai->mseed = seed;
    ai->oseed = (seed == EX)? OH : EX;
}

/* Get next best move for computer.*/
int move(aiplayer* ai){
    aimove result = minimax(ai, 2, ai->mseed);
    return result.pos;
}

/* Recursive minimax at level of depth for either maximizing or minimizing
    player.
    Return aimove of {score, row * COLS + col} */
aimove minimax(aiplayer* ai, int depth, sdstate seed){
    // Generate possible next moves in a vector<int> of row * ROWS + col
    vector* nextmoves = gen_moves(ai);

    // mseed is maximizing; while oseed is minimizing
    int bestScore = (seed == ai->mseed) ? INT_MIN : INT_MAX;
    int currentScore;
    int bestRow = -1;
    int bestCol = -1;

    if (vector_empty(nextmoves) || depth == 0)
        bestScore = eval(ai); // Gameover or depth reached, evaluate score
    else {
        int* move = nextmoves->items; //Store all possible moves we need
        for (int i=0; i < nextmoves->total; i++){
            // Try this move for the current "player seed"
            ai->brd->cells[move[i] / COLS][move[i] % COLS]->content = seed;
            if (seed == ai->mseed) {  // mseed (computer) is maximizing player
                currentScore = minimax(ai, depth - 1, ai->oseed).score;
                if (currentScore > bestScore){
                    bestScore = currentScore;
                    bestRow = move[i] / COLS;
                    bestCol = move[i] % COLS;
                }
            } else {  // oseed is minimizing player
                currentScore = minimax(ai, depth - 1, ai->mseed).score;
                if (currentScore < bestScore) {
                    bestScore = currentScore;
                    bestRow = move[i] / COLS;
                    bestCol = move[i] % COLS;
                }
            }
            // Undo move
            ai->brd->cells[move[i] / COLS][move[i] % COLS]->content = EMPTY;
        }
    }
    vector_free(nextmoves);
    aimove move = {.score = bestScore,.pos = bestRow * COLS + bestCol};
    return move;
}

/* Find all valid next moves.
    Return vector of moves in row * COLS + col, or empty vector if gameover */
vector* gen_moves(aiplayer* ai){
    vector* nextmoves = (vector*) malloc(sizeof(vector));
    vector_init(nextmoves); // allocate List
    // If gameover, i.e., no next move
    if (ai_has_won(ai, ai->mseed) || ai_has_won(ai, ai->oseed)) {
        return nextmoves;   // return empty list
    }

    // Search for empty cells and add to the List
    for (int row = 0; row < ROWS; ++row)
        for (int col = 0; col < COLS; ++col)
            if (ai->brd->cells[row][col]->content == EMPTY)
                vector_add(nextmoves,row * ROWS + col);

    return nextmoves;
}

/* The heuristic evaluation function for the current board
   @Return +100, +10, +1 for EACH 3-, 2-, 1-in-a-line for computer.
           -100, -10, -1 for EACH 3-, 2-, 1-in-a-line for opponent.
           0 otherwise   */
int eval(aiplayer* ai){
    int score = 0;
      // Evaluate score for each of the 8 lines (3 rows, 3 columns, 2 diagonals)
      score += evalline(ai, 0, 0, 0, 1, 0, 2);  // row 0
      score += evalline(ai, 1, 0, 1, 1, 1, 2);  // row 1
      score += evalline(ai, 2, 0, 2, 1, 2, 2);  // row 2
      score += evalline(ai, 0, 0, 1, 0, 2, 0);  // col 0
      score += evalline(ai, 0, 1, 1, 1, 2, 1);  // col 1
      score += evalline(ai, 0, 2, 1, 2, 2, 2);  // col 2
      score += evalline(ai, 0, 0, 1, 1, 2, 2);  // diagonal
      score += evalline(ai, 0, 2, 1, 1, 2, 0);  // alternate diagonal
      return score;
}

/* The heuristic evaluation function for the given line of 3 cells
   @Return +100, +10, +1 for 3-, 2-, 1-in-a-line for computer.
           -100, -10, -1 for 3-, 2-, 1-in-a-line for opponent.
           0 otherwise */
int evalline(aiplayer* ai,
            int row1, int col1, int row2, int col2,int row3, int col3){
    int score = 0;

    // First cell
    if (ai->brd->cells[row1][col1]->content == ai->mseed)
         score = 1;
    else if (ai->brd->cells[row1][col1]->content == ai->oseed)
         score = -1;

    // Second cell
    if (ai->brd->cells[row2][col2]->content == ai->mseed){
        if (score == 1)   // cell1 is mseed
            score = 10;
        else if (score == -1)  // cell1 is oseed
            return 0;
        else  // cell1 is empty
            score = 1;
    } else if (ai->brd->cells[row2][col2]->content == ai->oseed) {
        if (score == -1) // cell1 is oseed
            score = -10;
        else if (score == 1) // cell1 is mseed
            return 0;
        else // cell1 is empty
            score = -1;
    }

    // Third cell
    if (ai->brd->cells[row3][col3]->content == ai->mseed) {
        if (score > 0)  // cell1 and/or cell2 is mseed
            score *= 10;
        else if (score < 0) // cell1 and/or cell2 is oseed
            return 0;
        else   // cell1 and cell2 are empty
            score = 1;
    } else if (ai->brd->cells[row3][col3]->content == ai->oseed) {
        if (score < 0)  // cell1 and/or cell2 is oseed
            score *= 10;
        else if (score > 1)  // cell1 and/or cell2 is mseed
            return 0;
        else  // cell1 and cell2 are empty
            score = -1;
    }
    return score;
}

bool ai_has_won(aiplayer* ai, sdstate seed){
    int  win_patts[] = {
        0x1c0,   // 0b111 000 000 (row 2)
        0x038,   // 0b000 111 000 (row 1)
        0x007,   // 0b000 000 111 (row 0)
        0x124,   // 0b100 100 100 (col 2)
        0x092,   // 0b010 010 010 (col 1)
        0x049,   // 0b001 001 001 (col 0)
        0x111,   // 0b100 010 001 (diagonal)
        0x054    // 0b001 010 100 (opposite diagonal)
    };// msb is (2, 2) lsb is (0, 0)
    int pattern = 0x0;  // 9-bit pattern for the 9 cells
    for (int row = 0; row < ROWS; ++row)
        for (int col = 0; col < COLS; ++col)
            if (ai->brd->cells[row][col]->content == seed)
               pattern |= (1 << (row * COLS + col));

    for(int i=0; i < 8; i++)
        if((win_patts[i] & pattern) == win_patts[i])
            return true;
    return false;
}

void aclean(aiplayer* ai){
    free(ai);
}
