#include "vector.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "set.h"
#include "dict.h"

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

    return 0;
}
