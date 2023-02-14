#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>

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
    add,
    space,
    other
};

typedef struct token
{
    size_t tokentype;
    size_t prioroty;
    size_t parity;
    char   symbole;
} Token;

typedef struct array
{
    size_t len;
    Token** start;
} Array;

#endif
