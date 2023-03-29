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
    if(argc != 3)
        errx(3, "Not enough arguments");

    Array* arr = lexer(argv[1]);

    Stack *s = shunting_yard(arr);

    btree* ast = to_ast(s);

    automaton* a = new_automaton();
    build_enfa(a, ast);

    //print_dot_automaton(a);

    automaton* nfa = to_nfa(a);
    //print_dot_automaton(nfa);

    automaton* p = prune_automaton(nfa);
    //print_dot_automaton(p);

    automaton* d = determinize(p);
    //print_dot_automaton(d);

    GString* gs = g_string_new("");
    set* inter = d->initial_states;
    for(size_t i = 0; i < inter->capacity; ++i)
    {
        data* cur = inter->elements[i]->next;
        while(cur != NULL)
        {
            char* s = malloc(strlen(gs->str));
            strcpy(s, gs->str);
            size_t ins = insert_index("+", s, (size_t) atoi(cur->key));
            g_string_insert(gs, ins, cur->key);
            g_string_insert(gs, ins + strlen(cur->key), "+");
            cur = cur->next;
        }
    }
    char* origins = gs->str;

    int res = accepts(d, origins, argv[2]);

    if(res == 1)
        printf("The word is accepted!\n");
    else
        printf("The word is not accepted...\n");

    free_automaton(a);
    free_automaton(nfa);
    free_automaton(p);

    return 0;
}
