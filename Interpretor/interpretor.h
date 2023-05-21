#ifndef INTERPRETOR_H
#define  INTERPRETOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include "../Structures/token.h"
#include "../Structures/queue.h"
#include "../Structures/stack.h"
#include "../Structures/btree.h"
#include "../Structures/automaton.h"
#include "../Structures/array.h"
#include "../Structures/list.h"

Array* lexer(char *str);
Stack* shunting_yard(Array* input);
btree* to_ast(Stack* polish);
void print_ast(btree* ast, size_t offset);
void print2DUtil(btree* root, int space);
void to_dot_ast(btree* ast);
void aux(btree* ast, char* p);
#endif
