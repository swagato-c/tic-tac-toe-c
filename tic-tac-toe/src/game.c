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
#include "../include/game.h"
#include "../include/aiplayer.h"
#include <stdlib.h>
#include <stdio.h>

void gbuild(game* gm) {
    board* brd = (board*) malloc(sizeof(board));
    aiplayer* ai = (aiplayer*) malloc(sizeof(aiplayer));
    gm->game_board = brd; // allocate game-board
    gm->ai = ai; //set the ai-player
    gm->AI_PLAYING = false; //let it be ai's turn
    gm->AI_GAME = false; //let the game be human vs human
    bbuild(gm->game_board);
    abuild(gm->ai,gm->game_board);
    ginit(gm);
    bpaint(brd);
    do {
        player_move(gm,gm->current_player);
        bpaint(brd);
        update_game(gm,gm->current_player);
        if (gm->board_state == XWON)
            printf("'X' won! Bye!\n");
        else if (gm->board_state == OWON)
            printf("'O' won! Bye!\n");
        else if (gm->board_state == DRAW)
            printf("It's Draw! Bye!\n");
        gm->current_player = (gm->current_player == EX) ? OH : EX;
        if(gm->AI_GAME)
            gm->AI_PLAYING = !gm->AI_PLAYING;
    } while (gm->board_state == PLAYING);  // repeat until game-over
}

void ginit(game* gm) {
    binit(gm->game_board);
    do {
        printf("Enter 1 for human vs. human game\n");
        printf("Enter 2 for computer vs. human game\n");
        int ch;
        scanf("%d",&ch);
        if(ch == 1){
            break;
        } else if(ch == 2){
            gm->AI_GAME = true; //computer vs. human game
            int seed;
            printf("\t Human Enter 1 for X or Enter 2 for O \n");
            scanf("%d", &seed);
            set_seed(gm->ai, (seed == 1 )? OH : EX);
            gm->AI_PLAYING = (seed == 1) ? false : true;
            break;
        }
    } while(true);
    gm->current_player = EX;
    gm->board_state = PLAYING; // let the game begin!
}

void player_move(game* gm, sdstate seed) {
    bool valid = false;  // for validating input
    int row, col;
    do {
        if(!gm->AI_PLAYING){
            printf("Player %c, enter your move (row[1-3] column[1-3]):\n",
                (seed == EX)? 'X': 'O');
            scanf("%d %d",&row, &col);
            row--;
            col--;
        } else{
            int val = move(gm->ai);
            row = val / ROWS;
            col = val % COLS;
            printf("Computer entered it's move %c at (%d , %d):\n",
                (seed == EX)? 'X': 'O', row + 1, col + 1);
        }
        if (row >= 0 && row < ROWS && col >= 0 && col < COLS
                && gm->game_board->cells[row][col]->content == EMPTY) {
            gm->game_board->cells[row][col]->content = seed;
            gm->game_board->c_row = row;
            gm->game_board->c_col = col;
            update_patt(gm->game_board, seed);
            valid = true; // input okay, exit loop
        } else
            printf("This move at (%d , %d) is not valid. Try again ...\n",
                (row + 1),(col + 1));
      } while (!valid);   // repeat until input is valid
}

void update_game(game* gm, sdstate seed) {
    if (has_won(gm->game_board,seed)){
        gm->board_state = (seed == EX) ? XWON : OWON;
    }
    else if (is_draw(gm->game_board))
        gm->board_state = DRAW;
}

void gclean(game *gm) {
    bclean(gm->game_board);
    aclean(gm->ai);
    free(gm);
}
