#include "interpretor.h"
#include <stdlib.h>
#include <err.h>

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
#define DASH_ASCII (int) '-'
#define SPACE_ASCII (int) ' '

Array* lexer(char *str)
{
    size_t len = strlen(str);
    Array *result = malloc(sizeof(Array));
    result->len = 0;
    Queue* q = queue_new();
    result->q = q;
    int in_bracket = 0;

    for(size_t i = 0; i < len; i++)
    {
        Token *letter = calloc(1,sizeof(Token));
        switch(str[i])
        {
            case BACKSLASH_ASCII:
                letter->tokentype = backslash;
                letter->symbole = '\\';
                array_enqueue(result, letter);
                break;

            case DOT_ASCII:
                letter->tokentype = dot;
                letter->symbole = '.';
                letter->parity = 2;
                letter->prioroty = 1;
                array_enqueue(result, letter);
                break;

            case INTEROGATION_MARK_ASCII:
                letter->tokentype = interogation_mark;
                letter->symbole = '?';
                letter->parity = 1;
                array_enqueue(result, letter);
                break;

            case STAR_ASCII:
                letter->tokentype = star;
                letter->symbole = '*';
                letter->parity = 1;
                letter->prioroty = 2;
                array_enqueue(result, letter);
                break;
                
            case OPEN_BRACKET_ASCII:
                letter->tokentype = open_bracket;
                letter->symbole = '[';
                in_bracket = 1;

                if(i > 0)
                {
                    Token* pre = queue_peek(result->q);
                    if(pre->tokentype == other || pre->tokentype == close_parentheses 
                            || pre->tokentype == close_bracket)
                    {
                            Token* to_add = calloc(1,sizeof(Token));
                            if(to_add == NULL)
                                errx(EXIT_FAILURE, "lexer : malloc");

                            to_add->tokentype = dot;
                            to_add->symbole = '.';
                            to_add->parity = 2;
                            to_add->prioroty = 1;

                            array_enqueue(result,to_add);

                            Token* r = calloc(1,sizeof(Token));
                            if(r == NULL)
                                errx(EXIT_FAILURE, "lexer : malloc");
                            r->tokentype = open_parentheses;
                            r->symbole = '(';
                            array_enqueue(result,r);
                            break;
                    }
                }
                Token* replace = calloc(1,sizeof(Token));
                if(replace == NULL)
                    errx(EXIT_FAILURE, "lexer : malloc");
                replace->tokentype = open_parentheses;
                replace->symbole = '(';
                array_enqueue(result,replace);
                break;

            case CLOSE_BRACKET_ASCII:
                letter->tokentype = close_bracket;
                letter->symbole = ']';
                in_bracket = 0;
                Token* to_add = calloc(1,sizeof(Token));
                if(to_add == NULL)
                    errx(EXIT_FAILURE,"lexer : malloc");

                to_add->tokentype = close_parentheses;
                to_add->symbole = ')';
                array_enqueue(result, to_add);
                break;

            case PIPE_ASCII:
                letter->tokentype = pipe;
                letter->symbole = '|';
                array_enqueue(result, letter);
                break;

            case OPEN_PARENTHESES_ASCII:
                letter->tokentype = open_parentheses;
                letter->symbole = '(';

                if(i > 0)
                {
                    Token* pre = queue_peek(result->q);
                    if(pre->tokentype == other || pre->tokentype == close_parentheses 
                            || pre->tokentype == close_bracket)
                    {
                            Token* to_add = calloc(1,sizeof(Token));
                            if(to_add == NULL)
                                errx(EXIT_FAILURE, "lexer : malloc");

                            to_add->tokentype = dot;
                            to_add->symbole = '.';
                            to_add->parity = 2;
                            to_add->prioroty = 1;

                            array_enqueue(result,to_add);
                            array_enqueue(result,letter);
                            break;
                    }
                }
                array_enqueue(result,letter);
                break;

            case CLOSE_PARENTHESES_ASCII:
                letter->tokentype = close_parentheses;
                letter->symbole = ')';
                array_enqueue(result, letter);
                break;
    
            case ADD_ASCII:
                letter->tokentype = add;
                letter->symbole = '+';
                letter->parity = 2;
                letter->prioroty = 0;
                array_enqueue(result, letter);
                break;

            case DASH_ASCII:
                for(char j = str[i-1]+1; j < str[i+1]; ++j)
                {
                    Token* to_add = calloc(1,sizeof(Token));
                    Token* character = calloc(1,sizeof(Token));
                    if(to_add == NULL || character == NULL)
                        errx(EXIT_FAILURE,"lexer : malloc");
                    
                    to_add->tokentype = add;
                    to_add->symbole = '+';
                    to_add->parity = 2;
                    to_add->prioroty = 0;

                    character->tokentype = other;
                    character->symbole = j;

                    array_enqueue(result,to_add);
                    array_enqueue(result,character);

                }
                break;

//            case SPACE_ASCII:
//                continue;

            default:
                letter->tokentype = other;
                letter->symbole = str[i];
                if(i > 0)
                {
                    Token* pre = queue_peek(result->q);
                    if(pre->tokentype == other || pre->tokentype == close_parentheses 
                            || pre->tokentype == close_bracket)
                    {
                            Token* to_add = calloc(1,sizeof(Token));
                            if(to_add == NULL)
                                errx(EXIT_FAILURE, "lexer : malloc");

                            to_add->tokentype = in_bracket ? add : dot;
                            to_add->symbole = in_bracket ? '+' : '.';
                            to_add->parity = 2;
                            to_add->prioroty = (in_bracket+1)%2;

                            array_enqueue(result,to_add);
                            array_enqueue(result,letter);
                            break;
                    }
                }
                array_enqueue(result,letter);
                break;
        }
    }
    return result;
}
