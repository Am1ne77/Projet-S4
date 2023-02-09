#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "dict.h"

// Return the hash value of the key string
uint32_t hash_d(char *key)
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
dict* new_dict(size_t capacity)
{
    dict* d;
    d = malloc(sizeof(struct dict));
    if(d == NULL)
        errx(1,"new_set() : Error !");

    d->capacity = capacity;
    d->size = 0;

    d->elements = malloc(sizeof(struct pair*) * capacity);
    if(d->elements == NULL)
        errx(1,"new_set() : Error !");

    //allocate each cells of the array
    for(size_t i = 0; i < capacity; ++i)
    {
        pair* sentinel = malloc(sizeof(struct pair));
        if(sentinel == NULL)
        errx(1,"new_set() : Error !");

        sentinel->next = NULL;
        d->elements[i] = sentinel;
    }

    return d;
}


// Free a set
void free_dict(dict* d)
{
    for(size_t i = 0; i < d->capacity; ++i)
    {
        pair* curr = d->elements[i];
        while(curr != NULL)
        {
            pair* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(d->elements);
    free(d);
}


// Return 1 if key with hash i is in the set, 0 otherwise
size_t search_dict(dict* d, char* key, uint32_t i)
{
    for(pair* curr = (d->elements[i])->next; curr != NULL; curr = curr->next)
    {
        if(strcmp(key, curr->key) == 0)
            return 1;
    }
    return 0;
}

// Return the value assiociated with the key
char* get_value(dict* d, char* key)
{
    uint32_t i = hash_d(key) % (d->capacity);
    for(pair* curr = (d->elements[i])->next; curr != NULL; curr = curr->next)
    {
        if(strcmp(key, curr->key) == 0)
            return curr->value;
    }

    errx(1, "get_value() : key not in dict ! ");
}

// Return the set with key inserted in set
// if key already in, nothing is done to the set
void insert_dict(dict** d, char* key, char* value)
{
    uint32_t i = hash_d(key) % ((*d)->capacity);

    if(search_dict(*d, key, i))
        return;

    if(100 * (*d)->size / (*d)->capacity >= 75)
        expand_dict(d);

    pair* new_pair = malloc(sizeof(struct pair));
    new_pair->key = key;
    new_pair->value = value;
    new_pair->hkey = i;
    new_pair->next = (*d)->elements[i]->next;

    (*d)->elements[i]->next = new_pair;

    if(new_pair->next == NULL)
       (*d)->size += 1;
}

// Double the size of a set
void expand_dict(dict** p_dict)
{
    // new set with double the capacity
    dict* n_dict = new_dict(((*p_dict)->capacity)*2);

    for(size_t i = 0; i < (*p_dict)->capacity; ++i)
    {
        // reinsert the keys of the old set in the new set (new hash value)
        pair* curr = (*p_dict)->elements[i]->next;
        while(curr != NULL){
            insert_dict(&n_dict, curr->key, curr->value);
            curr = curr->next;
        }
    }

    free_dict(*p_dict);
    *p_dict = n_dict;
}

// Delete the key in the set, do nothing if key not in the set
void delete_dict(dict* d, char* key)
{
    uint32_t i = hash_d(key) % (d->capacity);

    pair* curr = d->elements[i]->next;
    pair* past = d->elements[i];
    while(curr != NULL)
    {
        // key found
        if(strcmp(curr->key,key) == 0){
            past->next = curr->next;
            free(curr);

            if(d->elements[i]->next == NULL)
                d->size = d->size -1;

            break;
        }
        past = curr;
        curr = curr->next;
    }
    return;
}
/*
// Return and delete random key from the set
char* pop_dict(dict* d)
{
    if(d->size == 0)
        errx(1, "pop() : cannot pop an element from an empty set !");

    char* key;
    for(size_t i = 0; i < d->capacity; ++i)
    {
        pair* curr = set->elements[i]->next;
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
// set2 is freed by the function
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
    free_set(set2);
}

// Not so pretty print of a set
void print_set(set* set)
{
    printf("---------set---------\n");
    printf("capacity = %zu ; size = %zu\n", set->capacity, set->size);
    for(size_t i = 0; i < set->capacity; ++i)
    {
        printf("|");
        data* curr = set->elements[i];
        do
        {
            curr = curr->next;
            if(curr == NULL)
                printf(" ");
            else
                printf("%s", curr->key);
            printf("|");
        }while(curr != NULL);
        printf("\n");
    }

    printf("---------end---------\n");

    printf("\n");
}
*/
