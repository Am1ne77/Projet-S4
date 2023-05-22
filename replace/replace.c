#include "../Interpretor/interpretor.h"
#include "replace.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>

int in(char c, char* s)
{
    for(size_t i = 0; s[i] != 0; ++i)
    {
        if(s[i] == c)
            return 1;
    }
    return 0;
}

char* get_word(char* string, char* delim, size_t* i, size_t n)
{
    char* res = malloc(sizeof(char)*(n - *i));
    size_t j = 0;
    while(*i < n && !in(string[*i],delim))
    {
        res[j] = string[*i];
        ++j;
        ++(*i);
    }
    if(j == 0)
    {
        if(*i == n)
            return NULL;

        res[j] = string[*i];
        res[j+1] = 0;
        ++(*i);
    }
    else
        res[j] = 0;
    return res;
}

void replace(char* file_path, char* pattern, char* new_word, char* delim)
{
    FILE* file;
    FILE* tmp_file;

    char* word;
    char* line = NULL;
    size_t line_size = 0;

    size_t i = 0;
    size_t len;

    automaton* a = create_dfa(to_ast(shunting_yard(lexer(pattern))));

    file = fopen(file_path,"r");
    tmp_file = fopen("tmp.txt","w");
    if(file == NULL || tmp_file == NULL)
        errx(EXIT_FAILURE, "cannot open the files.");

    while(getline(&line, &line_size, file) != -1)
    {
        len = strlen(line);
        word = get_word(line, delim, &i, len);
        while(word != NULL){
            fputs(accepts_word(a,get_origins(a),word) ? new_word : word,tmp_file);
            word = get_word(line, delim, &i, len);
        }
        i = 0;
    }
    free(line);
    fclose(file);
    fclose(tmp_file);

    remove(file_path);
    rename("tmp.txt",file_path);

}

linked_list* find(char* file_path, char* pattern, char* delim)
{
    FILE* file;

    char* word;
    char* line = NULL;
    size_t line_size = 0;
    size_t line_nb = 1;
    
    size_t start = 0;
    size_t i = 0;
    size_t len;

    linked_list* res = new_list();
    automaton* a = create_dfa(to_ast(shunting_yard(lexer(pattern))));

    file = fopen(file_path,"r");
    if(file == NULL)
        errx(EXIT_FAILURE, "Cannot open the file.");

    while(getline(&line, &line_size, file) != -1)
    {
        len = strlen(line);
        start = i;
        word = get_word(line, delim, &i, len);
        while(word != NULL)
        {
            if(accepts_word(a,get_origins(a),word))
            {
                size_t data1 = line_nb;
                char* data2 = get_substring(line, start, i-1);
                insert_list(res, data1, data2);
            }
            start = i;
            word = get_word(line, delim, &i, len);
        }
        i = 0;
        ++line_nb;
    }
    free(line);
    fclose(file);

    return res;
}

char* get_substring(char* s, size_t start, size_t end)
{
    size_t j = 0;
    char* res = malloc(sizeof(char)*(end-start+2));
    for(size_t i = start; i <= end; ++i){
        res[j] = s[i];
        ++j;
    }
    res[j] = 0;
    return res;
}

void display(linked_list* l)
{
    FILE* file;
    file = fopen("bin/res","w+");

    linked_list* p = l->next;
    while(p != NULL)
    {
        size_t data1 = (size_t)p->data1;
        char* data2 = (char*)p->data2;
        fprintf(file,"line %li: %s\n",data1,data2);
        p = p->next;
    }
    fclose(file);
    //rename("res","../bin/res");
}
