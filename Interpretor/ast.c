#include <stdlib.h>
#include <err.h>
#include "../Structures/btree.h"
#include "../Structures/stack.h"
#include "interpretor.h"

btree* to_ast(Stack* polish)
{
    Token* t = (Token*) stack_pop(polish);

    btree* ast = malloc(sizeof(ast));
    ast->key = (Token*)t;
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

void print_ast(btree* ast, size_t offset)
{
    if(ast == NULL)
        return;

    for(size_t i = 0; i < offset; ++i)
        printf(" ");
    
    Token* node = (Token*)ast->key;
}
