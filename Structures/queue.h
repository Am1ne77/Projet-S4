#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include "token.h"

typedef struct queue
{
    struct queue* next;
    Token* data;
} Queue;

Queue* queue_new();
size_t queue_is_empty(Queue *q);
void queue_enqueue(Queue *q, Token *t);
Token* queue_dequeue(Queue *q);
Token* queue_peek(Queue *q);
void queue_destroy(Queue *q);
void print_queue(Queue *q);

#endif
