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

//Returns 1 if the word is accepted by the automaton, 0 otherwise
int accepts_word(automaton* a, char* origins, char* word);

//Returns + parsed string of the initial states of the automaton
char* get_origins(automaton* a);

//Returns the dfa of the ast
automaton* create_dfa(btree* ast);

//Function that frees an automaton
void free_automaton(automaton* autom);

//Function that prints the automaton adjlitsts on the stdout
void print_automaton(automaton* autom);

//Funciton that prints the dot representation of an automaton
void print_dot_automaton(automaton* autom);

automaton* new_automaton();
void build_enfa(automaton* autom, btree* regex);





#endif
