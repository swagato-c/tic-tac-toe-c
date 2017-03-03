#include "board.h"

typedef struct game {
    board game_board;
    gstate board_state;
    sdstate current_player;
} game;

void build(game*);
void init(game*);
void player_move(game*);
void update_game(game*);
