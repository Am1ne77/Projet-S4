#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

typedef struct array
{
    size_t len;
    Queue* q;
} Array;

void array_push(Array* arr, Token* t);
Token* array_pop(Array* arr);
void array_destroy(Array* arr);
#endif
