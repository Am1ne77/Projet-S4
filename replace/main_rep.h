#ifndef MAIN_REP_H
#define MAIN_REP_H
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
#include "../Interpretor/interpretor.h"
//#include <fcntl.h>

int in(char c, char* s);

char* get_word(char* string, char* delim, size_t* i, size_t n);

void replace(char* file_path, char* pattern, char* new_word);
#endif

