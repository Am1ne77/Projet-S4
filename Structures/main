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

    automaton* a = new_automaton();
/*    add_state_automaton(a);
    add_state_automaton(a);
    add_state_automaton(a);
    add_state_automaton(a);

    add_arc_automaton(a, 0, 2, "a");
    add_arc_automaton(a, 1, 0, "b");
    add_arc_automaton(a, 0, 3, "c");
    add_arc_automaton(a, 3, 1, "b");
*/

    btree* root;
    root = malloc(sizeof(struct btree));
    root->key = "+";

    btree* la;
    la = malloc(sizeof(struct btree));
    la->key = "a";
    la->child1 = NULL;
    la->child2 = NULL;
    root->child1 = la;

    btree* dot;
    dot = malloc(sizeof(struct btree));
    dot->key = ".";
    root->child2 = dot;

    btree* lb;
    lb = malloc(sizeof(struct btree));
    lb->key = "b";
    lb->child1 = NULL;
    lb->child2 = NULL;
    dot->child1 = lb;

    btree* star;
    star = malloc(sizeof(struct btree));
    star->key = "*";
    dot->child2 = star;

    btree* lc;
    lc = malloc(sizeof(struct btree));
    lc->key = "c";
    star->child1 = lc;
    lc->child1 = NULL;
    lc->child2 = NULL;

    build_enfa(a, root);

    //print_automaton(a);

    print_dot_automaton(a);

    free_automaton(a);

    free(root);
    free(la);
    free(dot);
    free(star);
    free(lb);
    free(lc);

    return 0;
}
