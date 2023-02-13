#ifndef INTERPRETOR_H
#define  INTERPRETOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>

enum tokentype
{
    backslash,
    dot,
    interogation_mark,
    star,
    open_bracket,
    close_bracket,
    pipe,
    open_parentheses,
    close_parentheses,
    other
};

typedef struct token
{
    size_t tokentype;
    size_t prioroty;
    size_t parity;
} Token;

Token** lexer(char *str);

// inserer struct AST parser(token *t_str);
#endif
