#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "set.h"

int main()
{
    set* set1 = new_set(4);
    set1 = insert_set(set1, "France");
    set1 = insert_set(set1, "Spain");
    set1 = insert_set(set1, "Jamaica");
    set1 = insert_set(set1, "Cuba");
    print_set(set1);
    set* set2 = new_set(4);
    set2 = insert_set(set2, "Iraq");
    set2 = insert_set(set2, "Turkey");
    union_set(&set1, set2);
    print_set(set1);

    printf("pop = %s\n", pop_set(set1));
    print_set(set1);
    free_set(set1);

    return 0;
}
