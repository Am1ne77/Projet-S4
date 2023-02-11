#include <stdio.h>
#include "set.h"
#include "dict.h"
#include "automaton.h"

/*struct ENFA* new_enfa(set* allstates, set* initial_states, set* final_states,
        set* alphabet, dict* edges)
{

}
*/


void add_state(struct ENFA* enfa)
{
    int add_state = atoi(max_set(enfa->all_states) + 1);
    char name_state[25];
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
