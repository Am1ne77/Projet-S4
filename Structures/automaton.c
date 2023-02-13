#include <stdio.h>
#include <string.h>
#include <math.h>
#include <err.h>
#include "set.h"
#include "dict.h"
#include "automaton.h"


automaton* new_automaton()
{
    automaton* autom;
    autom = malloc(sizeof(struct automaton));
    autom->order = 0;
    autom->initial_states = new_set(4);
    autom->final_states = new_set(4);
    autom->alphabet = new_set(4);
    autom->adjlists = malloc(sizeof(struct list));
    autom->adjlists->arc = NULL;
    autom->adjlists->next_arc = NULL;
    autom->adjlists->next_node = NULL;
    return autom;
}

void add_state_automaton(automaton* autom)
{
    autom->order += 1;
    struct list* search = autom->adjlists;
    while(search->next_node != NULL)
    {
        search = search->next_node;
    }
    struct list* l = malloc(sizeof(struct list));
    l->next_arc = NULL;
    l->next_node = NULL;
    l->arc = NULL;
    search->next_node = l;
}

list* find_list(automaton* autom, size_t index)
{
    if(index >= autom->order)
        errx(1, "Trying to access inexistant node");
    struct list* search = autom->adjlists->next_node;
    while(search != NULL && index > 0)
    {
        search = search->next_node;
        index--;
    }
    return search;
}

void add_arc_automaton(automaton* autom, size_t start, size_t end,
        char* letter)
{

    if(start >= autom->order || end >= autom->order)
        errx(1, "Trying to add an arc to an inexistant node\n");

    insert_set(&(autom->alphabet), letter);

    struct list* search = find_list(autom, start);
    while(search->next_arc != NULL)
    {
        if(search->next_arc->arc->end == end
                && strcmp(search->next_arc->arc->letter, letter) == 0)
            return;
        search = search->next_arc;
    }
    struct arc* a = malloc(sizeof(struct arc));
    a->end = end;
    a->letter = letter;
    struct list* l = malloc(sizeof(struct list));
    l->arc = a;
    l->next_arc = NULL;
    l->next_node = NULL;
    search->next_arc = l;
}


void build_enfa(automaton* autom)
{
    add_state_automaton(autom);
    add_state_automaton(autom);
    insert_set(&(autom->initial_states), "0");
    insert_set(&(autom->final_states), "1");
}


void print_automaton(automaton* autom)
{
    printf("---------------automaton---------------\n");

    printf("Automaton number of states: %zu\n", autom->order);

    printf("Initial States:\n{ ");
    set* set = autom->initial_states;
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* c = set->elements[i]->next;
        while(c != NULL)
        {
            printf("%s ", c->key);
            c = c->next;
        }
    }
    printf("}\n");

    printf("Final States:\n{ ");
    set = autom->final_states;
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* c = set->elements[i]->next;
        while(c != NULL)
        {
            printf("%s ", c->key);
            c = c->next;
        }
    }
    printf("}\n");



    printf("Alphabet:\n{ ");
    set = autom->alphabet;
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* c = set->elements[i]->next;
        while(c != NULL)
        {
            printf("%s ", c->key);
            c = c->next;
        }
    }
    printf("}\n");

    printf("Adjlists:\n");
    list* l = autom->adjlists->next_node;
    for(size_t i = 0; i < autom->order; ++i)
    {
        printf("%zu -> |", i);
        list* arcs = l->next_arc;
        while(arcs != NULL)
        {
            printf(" (%s, %zu) |", arcs->arc->letter, arcs->arc->end);
            arcs = arcs->next_arc;
        }
        printf("\n");
        l = l->next_node;
    }

    printf("------------------end------------------\n");
}
