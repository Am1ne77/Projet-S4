#ifndef MAIN_REP_H
#define MAIN_REP_H
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
#include "../Interpretor/interpretor.h"

int get_pattern(char* line, ssize_t len_line, char* pattern, size_t* len_pattern);

void insert_string(char* dest, char* src, size_t len_dest, size_t len_src);
#endif

