#ifndef _SET_H_
#define _SET_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct data
{
    uint32_t hkey;
    char *key;
    struct data *next;
}data;

typedef struct set
{
    size_t size;
    size_t capacity;
    struct data **elements;
}set;

uint32_t hash(char *key);

set* new_set(size_t capacity);

void free_set(set* set);

size_t search(set* set, char* key, uint32_t i);

set* insert(set* set, char* key);

void expand_set(set** old_set);

void print_set(set* set);

#endif
