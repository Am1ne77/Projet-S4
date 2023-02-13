#include "interpretor.h"
#include <stdlib.h>

#define BACKSLASH_ASCII (int) '\\'
#define DOT_ASCII (int) '.' 
#define INTEROGATION_MARK_ASCII (int) '?'
#define STAR_ASCII (int) '*'
#define OPEN_BRACKET_ASCII (int) '['
#define CLOSE_BRACKET_ASCII (int) ']'
#define PIPE_ASCII (int) '|'
#define OPEN_PARENTHESES_ASCII (int) '('
#define CLOSE_PARENTHESES_ASCII (int) ')'

Token** lexer(char *str)
{
    size_t len = strlen(str);
    Token **result = malloc(sizeof(Token*)*len);

    for(size_t i = 0; i < len; i++)
    {
        Token *letter = calloc(1,sizeof(Token));
        switch(str[i])
        {
            case BACKSLASH_ASCII:
                letter->tokentype = backslash;
                break;

            case DOT_ASCII:
                letter->tokentype = dot;
                break;

            case INTEROGATION_MARK_ASCII:
                letter->tokentype = interogation_mark;
                break;

            case STAR_ASCII:
                letter->tokentype = star;
                break;
                
            case OPEN_BRACKET_ASCII:
                letter->tokentype = open_bracket;
                break;

            case CLOSE_BRACKET_ASCII:
                letter->tokentype = close_bracket;
                break;

            case PIPE_ASCII:
                letter->tokentype = pipe;
                break;

            case OPEN_PARENTHESES_ASCII:
                letter->tokentype = open_parentheses;
                break;

            case CLOSE_PARENTHESES_ASCII:
                letter->tokentype = close_parentheses;
                break;

            default:
                letter->tokentype = other;
        }
        result[i] = letter;
    }

    return result;
}
