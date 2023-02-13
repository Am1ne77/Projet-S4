#include "stack.h"

Stack* stack_new(size_t capacity)
{
    Stack* s = malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;
    s->data = malloc(capacity * sizeof(void*));
    return s;
}

size_t stack_is_empty(Stack *s)
{
    return s->top == 0;
}

void stack_push(Stack *s, void* v)
{
    s->data[s->top++] = v;
}

void* stack_pop(Stack *s)
{
    return s->data[--s->top];
}

void stack_destroy(Stack *s)
{
    free(s->data);
    free(s);
}

void stack_display(Stack *s)
{
    printf("[");
    for(size_t i = 0; i != s->top; i = (i+1)%s->capacity)
    {
        printf(" %c ", s->data[i]->symbole);
    }
    printf("]\n");
}

