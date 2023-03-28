#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include "queue.h"
#include "token.h"

typedef struct array
{
    size_t len;
    Queue* q;
} Array;

void array_enqueue(Array* arr, Token* t);
Token* array_dequeue(Array* arr);
void array_destroy(Array* arr);
#endif
