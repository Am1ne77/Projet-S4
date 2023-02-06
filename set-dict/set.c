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

// Return a new set of capacity capacity
set* new_set(size_t capacity)
{
	set* set;
   	set = malloc(sizeof(struct set));
	if(set == NULL)
		errx(1,"new_set() : Error !");
	set->capacity = capacity;
	set->size = 0;
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

/*

set* new_set(size_t capacity) 
{
    set* set = (struct set*) malloc(sizeof(set));
    set->capacity = capacity;
    set->size = 0;
    set->elements = (data**) malloc(sizeof(data*) * set->capacity);
    memset(set->elements, 0, sizeof(data*) * set->capacity);
    return set;
}*/


// free a set
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


// return 1 if key with hash i is in the set, 0 otherwise
size_t search(set* set, char* key, uint32_t i)
{

    for(data* curr = (set->elements[i])->next; curr != NULL; curr = curr->next){
	if(strcmp(key, curr->key) == 0)
		return 1;
    }
	return 0;
}


// insert key in set if key not already in, nothing otherwise
set* insert(set* set, char* key)
{
    uint32_t i = hash(key) % (set->capacity);

    if(search(set, key, i))
        return set;

    if(100 * set->size / set->capacity >= 75)
        expand_set(&set);

    data* new_data = malloc(sizeof(struct data));
    new_data->key = key;
    new_data->hkey = i;
    new_data->next = set->elements[i]->next;

    set->elements[i]->next = new_data;

    if(new_data->next == NULL)
        set->size+=1;

    return set;
}


// double the size of the set and recalculate new hash for all the elements
void expand_set(set** p_set)
{
    set* n_set = new_set(((*p_set)->capacity)*2);
    
    for(size_t i = 0; i < (*p_set)->capacity; ++i)
    {
        for(data* curr = (*p_set)->elements[i]->next; curr != NULL; curr = curr->next)
            n_set = insert(n_set, curr->key);
    }
    
    free_set(*p_set);
    *p_set = n_set;
}

void delete(set* set, char* key)
{
	uint32_t i = hash(key) % (set->capacity);
	data* curr = set->elements[i]->next;
	data* past = set->elements[i];
	while(curr != NULL)
	{
		if(strcmp(curr->key,key) == 0){
			past->next = curr->next;
			free(curr);
			if(set->elements[i]->next == NULL)
				set->size = set->size -1;
                        break;
		}

		past = curr;
		curr = curr->next;
	}

}

void set_union(set** set1, set* set2)
{
	if((*set1)->capacity < set2->capacity)
		set_union(&set2, *set1);

	else
	{
		for(size_t i = 0; i < set2->capacity; ++i){
			for(data* curr = set2->elements[i]->next; curr != NULL; curr = curr->next)
				insert(*set1, curr->key);
        }
        free(set2);
    }
}

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

    printf("-------end---------\n");
}


int main()
{
    set* set = new_set(4);
    print_set(set);
    set = insert(set, "paris");
    set = insert(set, "madrid");
    set = insert(set,"aaa");
    set = insert(set,"aaa");
    print_set(set);
    set = insert(set, "g");
    print_set(set);
    set = insert(set, "h");
    delete(set, "paris");
    print_set(set);
    //printf("size = %li, capacity = %li\n",set->size,set->capacity);
    //printf("found(paris) = %li\n", search(set, "paris", hash("paris")%set->capacity));
    free_set(set);
    return 0;
}
