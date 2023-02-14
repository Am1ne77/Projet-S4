#ifndef _BTREE_H
#define _BTREE_H

#include <stdlib.h>

typedef struct btree
{
    char* key;
    struct btree *child1;
    struct btree *child2;
}btree;

#endif
