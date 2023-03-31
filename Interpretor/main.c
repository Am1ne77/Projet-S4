#include "interpretor.h"
#include "../Structures/automaton.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>

void print_token(Token *tok, size_t i)
{
    printf("Token %lu:\n", i);
    printf("   tokentype %lu:\n", tok->tokentype);
    printf("   priority %lu:\n", tok->prioroty);
    printf("   parity %lu:\n\n", tok->parity);
}

void print_token_list(Array* arr, char *str)
{
    printf("String:\n %s\n\n", str);
    for(size_t i = 0; i < arr->len; i++)
    {
        printf("Char %lu: %c\n", i, str[i]);
        print_token(queue_dequeue(arr->q), i);
    }
}


int main(int argc, char *argv[])
{
    if(argc != 3)
        errx(3, "Not enough arguments");

    Array* arr = lexer(argv[1]);

    Stack *s = shunting_yard(arr);

    btree* ast = to_ast(s);

    automaton* a = create_dfa(ast);
    char* origins = get_origins(a);
    int res = accepts_word(a, origins, argv[2]);

    if(res == 1)
        printf("The word is accepted!\n");
    else
        printf("The word is not accepted...\n");

    return 0;
}
