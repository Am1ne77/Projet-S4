#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "set.h"

// Return the hash value of the key string
uint32_t hash(char *key)
{
  //size_t i = 0;
  uint32_t hash = 0;
  while (*key != 0)
  {
    hash += *(key++);
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

// Return a new set of 'capacity' capacity
set* new_set(size_t capacity)
{
    set* set;
    set = malloc(sizeof(struct set));
    if(set == NULL)
        errx(1,"new_set() : Error !");

    set->capacity = capacity;
    set->size = 0;
    set->len = 0;

    set->elements = malloc(sizeof(struct data*) * capacity);
    if(set->elements == NULL)
        errx(1,"new_set() : Error !");

    //allocate each cells of the array
    for(size_t i = 0; i < capacity; ++i)
    {
        data* sentinel = malloc(sizeof(struct data));
        if(sentinel == NULL)
            errx(1,"new_set() : Error !");

        sentinel->next = NULL;
        set->elements[i] = sentinel;
    }

    return set;
}

// Free a set
void free_set(set* set)
{
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* curr = set->elements[i];
        while(curr != NULL)
        {
            data* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(set->elements);
    free(set);
}


// Return 1 if key with hash i is in the set, 0 otherwise
size_t search_set(set* set, char* key)
{
    uint32_t i = hash(key) % (set->capacity);
    for(data* curr = (set->elements[i])->next; curr != NULL; curr = curr->next)
    {
        if(strcmp(key, curr->key) == 0)
            return 1;
    }
    return 0;
}


// Return the set with key inserted in set
// if key already in, nothing is done to the set
void insert_set(set** set, char* key)
{
    if(search_set(*set, key))
        return;

    if(100 * (*set)->size / (*set)->capacity >= 75)
        expand_set(set);

    uint32_t i = hash(key) % ((*set)->capacity);

    data* new_data = malloc(sizeof(struct data));
    new_data->key = key;
    new_data->hkey = i;
    new_data->next = (*set)->elements[i]->next;

    (*set)->elements[i]->next = new_data;

    if(new_data->next == NULL)
       (*set)->size += 1;
    (*set)->len++;
}

// Double the size of a set
void expand_set(set** p_set)
{
    // new set with double the capacity
    set* n_set = new_set(((*p_set)->capacity)*2);

    for(size_t i = 0; i < (*p_set)->capacity; ++i)
    {
        // reinsert the keys of the old set in the new set (new hash value)
        data* curr = (*p_set)->elements[i]->next;
        while(curr != NULL){
            insert_set(&n_set, curr->key);
            curr = curr->next;
        }
    }

    free_set(*p_set);
    *p_set = n_set;
}

// Delete the key in the set, do nothing if key not in the set
void delete_set(set* set, char* key)
{
    uint32_t i = hash(key) % (set->capacity);

    data* curr = set->elements[i]->next;
    data* past = set->elements[i];
    while(curr != NULL)
    {
        // key found
        if(strcmp(curr->key,key) == 0){
            past->next = curr->next;
            free(curr);

            set->len--;

            if(set->elements[i]->next == NULL)
                set->size = set->size -1;

            break;
        }
        past = curr;
        curr = curr->next;
    }
    return;
}

// Return and delete random key from the set
char* pop_set(set* set)
{
    if(set->size == 0)
        errx(1, "pop() : cannot pop an element from an empty set !");

    char* key;
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* curr = set->elements[i]->next;
        if(curr != NULL) //first data found in the set
        {
            key = curr->key;
            delete_set(set, key);
            break;
        }
    }
    return key;
}

// Return, in set1 the union of the two sets
void union_set(set** set1, set* set2)
{
    for(size_t i = 0; i < set2->capacity; ++i)
    {
        data* curr = set2->elements[i]->next;
        while(curr != NULL){
            insert_set(set1, curr->key);
            curr = curr->next;
        }
    }
}

// Not so pretty print of a set
void print_set(set* set)
{
    printf("---------set---------\n");
    printf("capacity = %zu ; size = %zu\n\n", set->capacity, set->size);
    for(size_t i = 0; i < set->capacity; ++i)
    {
        printf("Bucket %zu: ", i + 1);
        data* curr = set->elements[i];
        do
        {
            curr = curr->next;
            if(curr == NULL)
                printf("[empty] ");
            else
                printf("[%s] ", curr->key);
        }while(curr != NULL);
        printf("\n");
    }

    printf("---------end---------\n");
}

//Returns the max value of a set
char* max_set(set* set)
{
    char* max = "";
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* curr = set->elements[i]->next;
        while(curr != NULL)
        {
            if(strcmp(curr->key, max) > 0)
                max = curr->key;
            curr = curr->next;
        }
    }
    return max;
}
