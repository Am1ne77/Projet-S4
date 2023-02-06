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

// Return the hash value of the key string
uint32_t hash(char *key);

// Return a new set of 'capacity' capacity
set* new_set(size_t capacity);

// Free a set
void free_set(set* set);

// Return 1 if key with hash i is in the set, 0 otherwise
size_t search_set(set* set, char* key, uint32_t i);

// Return the set with key inserted in set
// if key already in, nothing is done to the set
void insert_set(set** set, char* key);

// Double the size of the set
void expand_set(set** old_set);

// Delete the key in the set, do nothing if key not in the set
void delete_set(set* set, char* key);

// Return and delete random key from the set
char* pop_set(set* set);

// Return, in set1 the union of the two sets
// set2 is freed by the function
void union_set(set** set1, set* set2);

// Not so pretty print of a set
void print_set(set* set);

#endif
