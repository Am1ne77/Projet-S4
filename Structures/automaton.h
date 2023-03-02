#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "dict.h"
#include "set.h"
#include "vector.h"
#include "btree.h"

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

void build_enfa(automaton* autom, btree* regex);

set* get_epsilon_closure(automaton* autom, char* origin);

automaton* to_nfa(automaton* autom);

void free_automaton(automaton* autom);

void print_automaton(automaton* autom);

void print_dot_automaton(automaton* autom);

#endif
