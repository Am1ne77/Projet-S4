#include <stdio.h>
#include <string.h>
#include "set.h"
#include "dict.h"
#include "automaton.h"

const char delim[2] = "+";

struct ENFA* new_enfa(set* all_states, set* initial_states, set* final_states,
        set* alphabet, set* edges, dict* labels)
{
    struct ENFA* enfa;
    enfa = malloc(sizeof(struct ENFA));
    enfa->all_states = all_states;
    enfa->alphabet = alphabet;
    insert_set(&(enfa->alphabet), "ɛ");
    enfa->initial_states = initial_states;
    enfa->final_states = final_states;
    if(enfa->initial_states->len == 0)
    {
        insert_set(&(enfa->initial_states), "0");
        insert_set(&(enfa->all_states), "0");
    }

    if(labels->size != 0)
        enfa->labels = labels;
    else
    {
        for(size_t i = 0; i < enfa->all_states->len; ++i)
        {
            char num[20];
            sprintf(num, "%zu", i);
            printf("%s\n", num);
            insert_dict(&(labels), num, num);
        }
        enfa->labels = labels;
    }

    enfa->next_states = new_dict(4);
    for(size_t i = 0; i < enfa->all_states->capacity; ++i)
    {
        data* cur_state = enfa->all_states->elements[i]->next;
        while(cur_state != NULL)
        {
            for(size_t j = 0; j < enfa->alphabet->capacity; ++j)
            {
                data* cur_alp = enfa->alphabet->elements[j]->next;
                while(cur_alp != NULL)
                {
                    char* n;
                    asprintf(&n, "%zu+%zu", i, j);
                    insert_dict(&(enfa->next_states), n, new_set(4));
                    cur_alp = cur_alp->next;
                }
            }
            cur_state = cur_state->next;
        }
    }

    for(size_t i = 0; i < edges->capacity; ++i)
    {
        data* curr = edges->elements[i]->next;
        while(curr != NULL)
        {
            char* ptr;
            size_t l = strlen(curr->key) + 1;
            char cpy[l];
            strcpy(cpy, curr->key);
            ptr  = strtok(cpy ,delim);
            if(ptr != NULL && search_set(enfa->all_states, ptr))
            {
                char* first = ptr;
                ptr = strtok(NULL ,delim);
                if(ptr != NULL && search_set(enfa->alphabet, ptr))
                {
                    char* second = ptr;
                    ptr = strtok(NULL ,delim);
                    if(ptr != NULL && search_set(enfa->all_states, ptr))
                    {
                        char* n;
                        asprintf(&n, "%s+%s", first, second);
                        insert_dict(&(enfa->next_states), n, ptr);
                    }
                }
            }
            curr = curr->next;
        }
    }

    return enfa;
}



void add_state_enfa(struct ENFA* enfa)
{
    char* max = max_set(enfa->all_states);
    int add_state = atoi(max) + 1;
    size_t l = strlen(max);
    char name_state[l+1];
    sprintf(name_state, "%i", add_state);
    insert_set(&(enfa->all_states), name_state);
    for(size_t i = 0; i < enfa->alphabet->capacity; ++i)
    {
        data* curr = enfa->alphabet->elements[i]->next;
        while(curr != NULL)
        {
            char* n;
            asprintf(&n, "%s+%s", name_state, curr->key);
            insert_dict(&(enfa->next_states), n, new_set(4));
            curr = curr->next;
        }
    }
    insert_dict(&(enfa->labels), name_state, name_state);
}
