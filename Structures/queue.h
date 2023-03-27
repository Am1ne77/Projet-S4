#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include "token.h"

typedef struct queue
{
    struct Queue* next;
    Token* data; // Data (array)
} Queue;

Queue* queue_new();
size_t queue_is_empty(Queue *q);
void queue_enqueue(Queue *q, Token *t);
Token* queue_dequeue(Queue *q);
void queue_destroy(Queue *q);

#endif
