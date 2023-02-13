#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "dict.h"
#include "set.h"
#include "vector.h"

typedef struct arc
{
    size_t end;
    char* letter;
}arc;

typedef struct list
{
    struct arc* arc;
    struct list* next_arc;
    struct list* next_node;
}list;

typedef struct automaton
{
    size_t order;
    set* initial_states;
    set* final_states;
    set* alphabet;
    list* adjlists;
}automaton;


automaton* new_automaton();

void add_state_automaton(automaton* autom);

void add_arc_automaton(automaton* autom, size_t start, size_t end,
        char* letter);

#endif
