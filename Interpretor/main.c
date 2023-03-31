#include "interpretor.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc == 1)
        errx(3, "Not enough arguments");

    Array* arr = lexer(argv[1]);
    Stack *s = shunting_yard(arr);

    stack_display(s);
    //btree* ast = to_ast(s);
    //to_dot_ast(ast);
    //print_ast(ast,0);
    return 0;
}
