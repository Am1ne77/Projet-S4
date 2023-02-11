#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "dict.h"
#include "set.h"

typedef struct ENFA
{
    struct set* allstates;
    struct set* initial_states;
    struct set* final_states;
    struct set* alphabet;
    struct dict* edges;
    struct dict* next_states;
}ENFA;

void add_state(struct ENFA* enfa);

#endif
