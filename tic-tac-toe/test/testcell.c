#include <stdio.h>
#include <stdlib.h>
#include "../include/cell.h"

int main(void) {
    cell* c = (cell*) malloc(sizeof (cell));
    cell* c1 = (cell*) malloc(sizeof (cell));
    cbuild(c,0,0);
    cbuild(c1,3,0);
    content(c1,EX);
    printf("%c\n",cpaint(c));
    printf("%c\n",cpaint(c1));
    free(c);
    free(c1);
    return 0;
}
