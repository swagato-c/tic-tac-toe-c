#include <stdlib.h>
#include "../include/board.h"

int main(void) {
    board* b = (board *) malloc(sizeof(board));
    bbuild(b);
    bpaint(b);
    free(b);
}
