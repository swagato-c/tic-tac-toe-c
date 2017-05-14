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
#include <stdlib.h>
#include "../include/vector.h"

/*Construct the vector */
void vector_init(vector* v){
    v->capacity = 10;
    v->total = 0;
    v->items = (int*) malloc(sizeof(int) * v->capacity);
}

/*Total number of elements in the vector*/
int vector_total(vector* v){
    return v->total;
}

/*Resise the vector "v" by size "capacity"*/
void vector_resize(vector* v, int capacity){
    //printf("vector_resize: %d to %d\n", v->capacity, capacity);

    int *items = (int*) realloc(v->items, sizeof(int) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

/*Add "item" tothe end of the vector*/
void vector_add(vector* v, int item){
    if (v->capacity == v->total) // If full double thse size
        vector_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

void vector_set(vector* v, int index, int item){
    if (index >= 0 && index < v->total)
        v->items[index] = item;
}

int vector_get(vector* v, int index){
    if (index >= 0 && index < v->total)
        return v->items[index];
    return 0;
}

void vector_delete(vector* v, int index){
    if (index < 0 || index >= v->total)
        return;

    v->items[index] = 0;

    for (int i = index; i < v->total - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = 0;
    }
    v->total--;
    if (v->total > 0 && v->total == v->capacity / 4) //if
        vector_resize(v, v->capacity / 2);
}

void vector_free(vector* v){
    free(v->items);
}

bool vector_empty(vector* v){
    return v == NULL || v->total == 0;
}
