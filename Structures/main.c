#include "vector.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "set.h"
#include "dict.h"
#include "automaton.h"

int main()
{
    //Vector tests
    /*
    struct vector* v = vector_new();
    for(size_t i = 0; i < 100; i++)
    {
        vector_push(v, i);
    }
    vector_print(v);
    vector_free(v);
    */

    //Set tests
    /*
    set* set1 = new_set(4);
    insert_set(&set1, "France");
    insert_set(&set1, "Spain");
    insert_set(&set1, "Jamaica");
    insert_set(&set1, "Cuba");
    print_set(set1);
    set* set2 = new_set(4);
    insert_set(&set2, "Iraq");
    insert_set(&set2, "Turkey");
    union_set(&set1, set2);
    print_set(set1);

    printf("pop = %s\n", pop_set(set1));
    print_set(set1);
    free_set(set1);
    */

    set* all_states = new_set(4);
    insert_set(&all_states, "0");
    insert_set(&all_states, "1");
    insert_set(&all_states, "2");
    insert_set(&all_states, "3");
    insert_set(&all_states, "4");

    set* initial_states = new_set(4);
    insert_set(&initial_states, "0");

    set* final_states = new_set(4);
    insert_set(&final_states, "4");

    set* alphabet = new_set(4);
    insert_set(&alphabet, "a");
    insert_set(&alphabet, "b");

    set* edges = new_set(4);
    insert_set(&edges, "0+a+1");
    insert_set(&edges, "1+b+2");
    insert_set(&edges, "2+b+3");
    insert_set(&edges, "3+a+4");

    dict* labels = new_dict(4);

    ENFA* enfa = new_enfa(all_states, initial_states, final_states,
            alphabet, edges, labels);

    //add_state_enfa(enfa);

    return 0;
}
