#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "dict.h"
#include "set.h"
#include "vector.h"
#include "btree.h"

//Structure contained in the adjlists
//It has two fields:
//-end: the node this arc is leading to
//-letter the letter that arc has
typedef struct arc
{
    size_t end;
    char* letter;
}arc;


//Adjlists structure
typedef struct list
{
    struct arc* arc;
    struct list* next_arc;
    struct list* next_node;
}list;


//Automaton structure
typedef struct automaton
{
    size_t order;
    set* initial_states;
    set* final_states;
    set* alphabet;
    list* adjlists;
}automaton;

//Function that initializes an automaton
automaton* new_automaton();

//Function that adds a state to an automaton
void add_state_automaton(automaton* autom);


//Fonction that adds an arc to an automaton
void add_arc_automaton(automaton* autom, size_t start, size_t end,
        char* letter);

//Functtion that uses Thompson algorithm to build an automaton from an AST
void build_enfa(automaton* autom, btree* regex);


//Function that returns a set* of the epsilon closure of a node
set* get_epsilon_closure(automaton* autom, char* origin);


//Function that returns a new autom without epsilon-transitions
//ENFA to NFA
automaton* to_nfa(automaton* autom);

//Function that returns the accessible states from origin
set* get_accessible_states(automaton* autom, char* origin);

//Returns 1 if a state is useful, 0 otherwise
int is_useful(automaton* autom, char* origin);

//Prunes automaton
automaton* prune_automaton(automaton* autom);

//Function that frees an automaton
void free_automaton(automaton* autom);

//Function that prints the automaton adjlitsts on the stdout
void print_automaton(automaton* autom);

//Funciton that prints the dot representation of an automaton
void print_dot_automaton(automaton* autom);

#endif
