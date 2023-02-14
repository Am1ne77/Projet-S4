#include "interpretor.h"
#include "../Structures/automaton.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_token(Token *tok, size_t i)
{
    printf("Token %lu:\n", i);
    printf("   tokentype %lu:\n", tok->tokentype);
    printf("   priority %lu:\n", tok->prioroty);
    printf("   parity %lu:\n\n", tok->parity);
}

void print_token_list(Token **toklist, char *str)
{
    printf("String:\n %s\n\n", str);
    for(size_t i = 0; i < strlen(str); i++)
    {
        printf("Char %lu: %c\n", i, str[i]);
        print_token(toklist[i], i);
    }
}


int main(int argc, char *argv[])
{
    if(argc == 1)
        errx(3, "Not enough arguments");

    char i[10];
    scanf("%s", i);
    printf("\n");

    Array* arr = lexer(argv[1]);
    print_token_list(arr->start, argv[1]);

    scanf("%s", i);
    printf("\n");

    Stack *s = shunting_yard(arr);
    stack_display(s);

    printf("\n");

    scanf("%s", i);
    printf("\n");

    btree* ast = to_ast(s);
    to_dot_ast(ast);

    printf("\n");

    scanf("%s", i);
    printf("\n");

    automaton* a = new_automaton();
    build_enfa(a, ast);

    print_dot_automaton(a);

    free_automaton(a);

    return 0;
}
