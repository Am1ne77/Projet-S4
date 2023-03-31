#include <stdlib.h>
#include <err.h>
#include "../Structures/btree.h"
#include "../Structures/stack.h"
#include "interpretor.h"

#define COUNT 10

btree* to_ast(Stack* polish)
{
    Token* t = (Token*) stack_pop(polish);

    btree* ast = malloc(sizeof(btree));
    ast->key = &t->symbole;
    ast->child1 = NULL;
    ast->child2 = NULL;

    if(t->tokentype != other)
    {
        btree* child2 = to_ast(polish);
        ast->child2 = child2;
        if(t->tokentype != 3)
        {
            btree* child1 = to_ast(polish);
            ast->child1 = child1;
        }
    }

    return ast;
}

void aux(btree* ast, char* p)
{
    printf("\t\"%s\"->\"%s\";\n",p,ast->key);
    if(ast->child1 != NULL)
        aux(ast->child1, ast->key);
    if(ast->child2 != NULL)
        aux(ast->child2, ast->key);
}

void to_dot_ast(btree* ast)
{
    printf("digraph G {\n");
    printf("node [shape=circle]\n");
    if(ast->child1 != NULL)
        aux(ast->child1, ast->key);
    if(ast->child2 != NULL)
        aux(ast->child2, ast->key);
    printf("}\n");
}


void print_ast(btree* ast, size_t offset)
{
    if(ast == NULL)
        return;

    for(size_t i = 0; i < offset; ++i)
        printf(" ");
    
    printf("%s\n",ast->key);
    
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

void print2DUtil(btree* root, int space)
{
    if (root == NULL)
        return;

    space += COUNT;

    print2DUtil(root->child2, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s\n", root->key);

    print2DUtil(root->child1, space);
}
