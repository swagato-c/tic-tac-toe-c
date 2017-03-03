#include "cell.h"
#include <stdbool.h>

typedef struct board {
    cell cells[ROWS][COLS];
    int c_row, c_col;
    int ex_patt, oh_patt;
} board;

void build(board*);
void init(board*);
bool is_draw(board*);
void paint(board*);
bool has_won(board*);
