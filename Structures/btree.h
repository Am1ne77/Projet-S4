#ifndef _BTREE_H
#define _BTREE_H

#include "../Interpretor/interpretor.h"
#include <stdlib.h>

typedef struct btree
{
    Token *key;
    struct btree *child1;
    struct btree *child2;
}btree;

btree* to_ast(Queue* polish);

#endif
