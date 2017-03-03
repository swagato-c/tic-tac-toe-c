#include "constants.h"

typedef struct cell {
    sdstate content;
    int row, col;
} cell;

void build(cell*,int,int);
void clear(cell*);
void paint(cell*);
