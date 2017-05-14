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

#include "../include/board.h"
#include <stdlib.h>
#include <stdio.h>

void bbuild(board* brd) {
    for(int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++) {
            cell *c = (cell*) malloc(sizeof(cell));
            cbuild(c, i, j);
            brd->cells[i][j] = c;
        }
    }
}

void binit(board* brd) {
    for(int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            clear(brd->cells[i][j]);
}

/*Is the game draw?*/
bool is_draw(board* brd) {
    int draw_patt = 0x1ff; // 0b111 111 111
    return ((brd->ex_patt | brd->oh_patt) == draw_patt);
}

/*Returns true when player with "seed" has won after placing at (crow, ccol)*/
bool has_won(board *brd, sdstate seed){
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
    int patt = (seed == EX)? brd->ex_patt : brd->oh_patt;
    for(int i=0; i < 8; i++)
        if((win_patts[i] & patt) == win_patts[i])
            return true;
    return false;
}

/*Updates the pattern after the move has been made by player "seed"*/
void update_patt(board *brd, sdstate seed){
    int bit = brd->c_row * ROWS + brd->c_col;
    if(seed == EX)
        brd->ex_patt |= 0x1 << bit;
    else if (seed == OH)
        brd->oh_patt |= 0x1 << bit;
}

void bpaint(board *brd) {
    for(int i = 0; i < ROWS; i++){
        printf("\t\t");
        for (int j = 0; j < COLS; j++)
            printf("|%c", cpaint(brd->cells[i][j])); // each cell paints itself
        printf("|\n");
    }
}

void bclean(board* brd) {
    for(int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            cclean(brd->cells[i][j]);
    free(brd);
}
