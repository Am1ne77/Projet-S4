#ifndef MAIN_REP_H
#define MAIN_REP_H
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
#include "../Interpretor/interpretor.h"
//#include <fcntl.h>

void replace(char* file_path, char* pattern, char* new_word);

int get_pattern(char* line, ssize_t len_line, char* pattern, size_t* len_pattern);

//char* get_name(char* path);

void insert_string(char* dest, char* src, size_t len_dest, size_t len_src);
#endif

