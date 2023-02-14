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
#define ADD_ASCII (int) '+'
#define SPACE_ASCII (int) ' '

Array* lexer(char *str)
{
    size_t len = strlen(str);
    Array *result = malloc(sizeof(Array));
    result->len = 0;
    size_t pos = 0;
    Token **arr = malloc(sizeof(Token*)*len);

    for(size_t i = 0; i < len; i++)
    {
        Token *letter = calloc(1,sizeof(Token));
        switch(str[i])
        {
            case BACKSLASH_ASCII:
                letter->tokentype = backslash;
                letter->symbole = '\\';
                break;

            case DOT_ASCII:
                letter->tokentype = dot;
                letter->symbole = '.';
                letter->parity = 2;
                letter->prioroty = 1;
                break;

            case INTEROGATION_MARK_ASCII:
                letter->tokentype = interogation_mark;
                letter->symbole = '?';
                letter->parity = 1;
                break;

            case STAR_ASCII:
                letter->tokentype = star;
                letter->symbole = '*';
                letter->parity = 1;
                letter->prioroty = 2;
                break;
                
            case OPEN_BRACKET_ASCII:
                letter->tokentype = open_bracket;
                letter->symbole = '[';
                break;

            case CLOSE_BRACKET_ASCII:
                letter->tokentype = close_bracket;
                letter->symbole = ']';
                break;

            case PIPE_ASCII:
                letter->tokentype = pipe;
                letter->symbole = '|';
                break;

            case OPEN_PARENTHESES_ASCII:
                letter->tokentype = open_parentheses;
                letter->symbole = '(';
                break;

            case CLOSE_PARENTHESES_ASCII:
                letter->tokentype = close_parentheses;
                letter->symbole = ')';
                break;
    
            case ADD_ASCII:
                letter->tokentype = add;
                letter->symbole = '+';
                letter->parity = 2;
                letter->prioroty = 0;
                break;

            case SPACE_ASCII:
                continue;

            default:
                letter->tokentype = other;
                letter->symbole = str[i];
        }
        arr[pos] = letter;
        result->len ++;
        pos++;
    }
    result->start = arr;
    return result;
}
