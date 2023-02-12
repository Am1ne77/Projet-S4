#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "dict.h"
#include "set.h"

typedef struct ENFA
{
    struct set* all_states;
    struct set* initial_states;
    struct set* final_states;
    struct set* alphabet;
    struct set* edges;
    struct dict* next_states;
    struct dict* labels;
}ENFA;

ENFA* new_enfa(set* all_states, set* initial_states, set* final_states,
        set* alphabet, set* edges, dict* labels);

void add_state_enfa(struct ENFA* enfa);

#endif
