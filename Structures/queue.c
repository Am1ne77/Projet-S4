#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Queue* queue_new(size_t capacity)
{
    struct queue* q = malloc(sizeof(Queue));
    q->capacity = capacity;
    q->len = 0;
    q->start = 0;
    q->end = 0;
    q->data = malloc(capacity * sizeof(void*));
    return q;
}

size_t queue_is_empty(Queue *q)
{
    return q->end == q->start;
}

void queue_enqueue(Queue* q, void* v)
{
    q->data[q->end++] = v;
    if (q->end == q->capacity)
        q->end = 0;

    q->len++;
}


void* queue_dequeue(Queue* q)
{
    void* v = q->data[q->start++];
     
    if (q->start == q->capacity)
        q->start = 0;

    q->len--;
    return v;
}

void queue_destroy(struct queue* q)
{
    free(q->data);
    free(q);
}

void queue_display(Queue *q)
{
    printf("Queue\nLen: %lu\n[", q->len);
    for(size_t i = q->start; i != q->end; i = (i+1)%q->capacity)
    {
        printf(" %c ", q->data[i]->symbole);
    }
    printf("]\n");
}

