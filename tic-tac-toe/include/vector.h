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

#include <stdbool.h>

#ifndef VECTOR_H
#define  VECTOR_H

#define VECTOR_INIT_CAPACITY 10
typedef struct vector {
    int *items;
    int capacity;
    int total;
} vector;

void vector_init(vector*);
int vector_total(vector*);
void vector_resize(vector*, int);
void vector_add(vector*, int);
void vector_set(vector*, int, int);
int vector_get(vector*, int);
void vector_delete(vector*, int);
void vector_free(vector*);
bool vector_empty(vector*);

#endif
