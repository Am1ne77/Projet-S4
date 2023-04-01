#include "interpretor.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>

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
