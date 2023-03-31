#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

Queue* queue_new()
{
    Queue* q = calloc(1, sizeof(Queue));
    if(q == NULL)
        errx(EXIT_FAILURE,"queue_new : malloc");
    q->next = NULL;
    q->data = NULL;

    return q;
}

size_t queue_is_empty(Queue *q)
{
    return q->next == NULL;
}

void queue_enqueue(Queue* q, Token* t)
{
    Queue* tmp = malloc(sizeof(Queue));
    if(tmp == NULL)
        errx(EXIT_FAILURE,"enqueue : malloc");

    tmp->data = t;

    if(q->next == NULL) //the queue is empty
        tmp->next = tmp;
    
    else
    {
        tmp->next = q->next->next;
        q->next->next = tmp;
    }

    q->next = tmp;
}


Token* queue_dequeue(Queue* q)
{
    if(queue_is_empty(q))
        errx(EXIT_FAILURE,"dequeue : the queue is empty !");

    Queue* oldest = q->next->next;

    if(q->next == oldest)
        q->next = NULL;

    else
        q->next->next = oldest->next;

    Token* t = oldest->data;
    free(oldest);

    return t;
}

Token* queue_peek(Queue* q)
{
    if(queue_is_empty(q))
        errx(EXIT_FAILURE,"dequeue : the queue is empty !");

    return q->next->data;

}
void queue_destroy(Queue* q)
{
    while(!queue_is_empty(q))
        queue_dequeue(q);

    free(q);
}

void print_queue(Queue* q)
{
    printf("Queue : |");
    while(!queue_is_empty(q))
        printf("%c|",queue_dequeue(q)->symbole);
    printf("\n");
}
