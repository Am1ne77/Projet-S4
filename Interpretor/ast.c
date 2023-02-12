#include <stdlib.h>
#include <err.h>
#include "../Structures/btree.h"
#include "../Structures/queue.h"
#include "interpretor.h"

btree* to_ast(Queue* polish)
{
    Token* t = (Token*) queue_dequeue(polish);

    btree* ast = malloc(sizeof(ast));
    ast->key = t;
    ast->child1 = NULL;
    ast->child2 = NULL;

    if(t->tokentype != 9)
    {
        ast->child1 = to_ast(polish);
        if(t->tokentype != 3)
            ast->child2 = to_ast(polish);
    }

    return ast;
}

