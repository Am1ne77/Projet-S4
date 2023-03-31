#include "array.h"
#include "token.h"
#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void array_enqueue(Array* arr, Token* t)
{
    ++arr->len;
    queue_enqueue(arr->q, t);
}

Token* array_dequeue(Array* arr)
{
    --arr->len;
    Token* t = queue_dequeue(arr->q);
    return t;
}

void arraiy_destroy(Array* arr)
{
    queue_destroy(arr->q);
    free(arr);
}
