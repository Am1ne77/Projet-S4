#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include "token.h"

typedef struct stack
{
    size_t capacity;
    size_t top; // Top index (length)
    Token** data; // Data (array)
} Stack;

Stack* stack_new(size_t capacity);
size_t stack_is_empty(Stack *s);
void stack_push(Stack *s, void* v);
void* stack_pop(Stack *s);
void* stack_peek(Stack *s);
void stack_destroy(Stack *s);
void stack_display(Stack *s);

#endif
