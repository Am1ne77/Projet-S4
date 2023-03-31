#include "token.h"

void print_token(Token *tok, size_t i)
{
    printf("Token %lu:\n", i);
    printf("   symbole %c:\n", tok->symbole);
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


