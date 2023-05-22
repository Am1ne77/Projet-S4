#ifndef _MAIN_REP_H_
#define _MAIN_REP_H_
#define DELIM " \n\r,;./:!?'\"()[]\\{}"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
#include "../Interpretor/interpretor.h"

//return 1 if the character c is in the string s.
int in(char c, char* s);

//get the first word (as a substring between 2 characters in delim)
//of the string s of length n, starting at the index i.
char* get_word(char* string, char* delim, size_t* i, size_t n);

//replace all words (defined as a substrinf between 2 characters in delim)
//verifying the the pattern in the file given by the file path by the new word.
void replace(char* file_path, char* pattern, char* new_word, char* delim);

//store the words verifying the pattern and the line number they are in the file.
linked_list* find(char* file_path, char* pattern, char* delim);

//return the substring of s between the index start and end included.
char* get_substring(char* s, size_t start, size_t end);

//pretty print of the result of a call to find() with this format:
//line x: word
void display(linked_list* l);
#endif

