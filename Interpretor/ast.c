#include <stdlib.h>
#include <err.h>
#include "../Structures/btree.h"
#include "../Structures/stack.h"
#include "interpretor.h"

btree* to_ast(Stack* polish)
{
    Token* t = (Token*) stack_pop(polish);

    btree* ast = malloc(sizeof(btree));
    ast->key = (Token*)t;
    ast->child1 = NULL;
    ast->child2 = NULL;

    if(t->tokentype != 10)
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
    printf("%c\n",node->symbole);
    
    if(ast->child2 != NULL)
    {
        for(size_t k = 0; k < 3; ++k)
        {
            for(size_t i = 0; i < offset; ++i)
                printf(" ");
            printf("|");
            for(size_t j = 0; j < k; ++j)
                printf(" ");
            printf("\\\n");
        }
        print_ast(ast->child1, offset);
        print_ast(ast->child2, offset+3);
    }

    else if(ast->child1 != NULL)
    {
        for(size_t k = 0; k < 3; ++k)
        {
            for(size_t i = 0; i < offset; ++i)
                printf(" ");
            printf("|\n");
        }
        print_ast(ast->child1,offset);
    }
}
