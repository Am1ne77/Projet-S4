#ifndef _DICT_H_
#define _DICT_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct pair
{
    uint32_t hkey;
    char* key;
    char* value;
    struct pair* next;
}pair;

typedef struct dict
{
    size_t size;
    size_t capacity;
    struct pair **elements;
}dict;

// Return the hash value of the key string
uint32_t hash_d(char *key);

// Return a new dict of 'capacity' capacity
dict* new_dict(size_t capacity);

// Free a dict
void free_dict(dict* d);

// Return 1 if key with hash i is in the dict, 0 otherwise
size_t search_dict(dict* d, char* key, uint32_t i);

// Return the dict with key inserted in dict
// if key already in, nothing is done to the dict
void insert_dict(dict** d, char* key, char* value);

// Double the size of the dict
void expand_dict(dict** old_dict);

// Delete the key in the dict, do nothing if key not in the dict
void delete_dict(dict* d, char* key);

#endif

