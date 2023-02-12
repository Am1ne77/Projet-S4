#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>

typedef struct queue
{
    size_t capacity; // Max length
    size_t len; // Current length
    size_t start; // Start index
    size_t end; // End index
    void** data; // Data (array)
} Queue;

Queue* queue_new(size_t capacity);
size_t queue_is_empty(Queue *q);
void queue_push(Queue *q, void* v);
void* queue_dequeue(Queue *q);
void queue_destroy(Queue *q);

#endif
