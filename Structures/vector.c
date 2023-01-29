#include <err.h>
#include "vector.h"

struct vector *vector_new()
{
    struct vector* v;
    v = malloc(sizeof(struct vector));
    v->capacity = 1;
    v->size = 0;
    v->data = malloc(sizeof(int));
    return v;
}

void vector_free(struct vector *v)
{
    free(v->data);
    free(v);
}

void double_capacity(struct vector *v)
{
    v->data = realloc(v->data, 2 * v->capacity * sizeof(int));
    if(v->data == NULL)
        errx(1, "Not enough memory!");
    v->capacity *= 2;
}

void vector_push(struct vector *v, int x)
{
    if(v->capacity == v->size)
        double_capacity(v);
    v->data[v->size++] = x;
}

int vector_pop(struct vector *v, int *x)
{
    if(v->size == 0)
        return 0;
    *x = v->data[v->size - 1];
    v->size--;
    return 1;
}

int vector_get(struct vector *v, size_t i, int *x)
{
    if(i >= v->size)
        return 0;
    *x = v->data[i];
    return 1;
}

void vector_insert(struct vector *v, size_t i, int x)
{
    if(i > v->size)
        return;

    if(v->size == v->capacity)
        double_capacity(v);

    size_t index = v->size;
    while(index > i)
    {
        v->data[index] = v->data[index - 1];
        index--;
    }
    v->data[i] = x;
    v->size++;
}

int vector_remove(struct vector *v, size_t i, int *x)
{
    if(i >= v->size)
        return 0;
    *x = v->data[i];
    while(i < v->size - 1)
    {
        v->data[i] = v->data[i + 1];
        i++;
    }
    v->size--;
    return 1;
}

