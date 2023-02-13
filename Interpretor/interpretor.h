#ifndef INTERPRETOR_H
#define  INTERPRETOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include "../Structures/token.h"
#include "../Structures/queue.h"
#include "../Structures/stack.h"

Array* lexer(char *str);
Stack* shunting_yard(Array* input);

#endif
