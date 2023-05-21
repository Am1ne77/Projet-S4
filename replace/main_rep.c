#include "../Interpretor/interpretor.h"
#include "main_rep.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
//#include <fcntl.h>

int main(int argc, char *argv[])
{
    if(argc > 3)
        errx(EXIT_FAILURE,"failure");

    char* pattern = "a[0-9]*";
    char* new_word = "X";

    replace("test.txt",pattern, new_word);

    return 0;
}

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
        //printf("here\n");
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

void replace(char* file_path, char* pattern, char* new_word)
{
    FILE* file;
    FILE* tmp_file;

    char* delim = " .\n";
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
            //printf("there\n");
        }
        i = 0;
    }
    free(line);
    fclose(file);
    fclose(tmp_file);

    remove(file_path);
    rename("tmp.txt",file_path);

}



/*
void replace(char* file_path, char* pattern, char* new_word)
{
    FILE* file;
    FILE* tmp_file;

    char* line = NULL;

    size_t line_size = 0;
    size_t len_pattern = 0;
    size_t len_word = strlen(new_word);
    ssize_t len_line;

    int position = 0;
    int test = 0;
    int start;
    int end;

    automaton* a = create_dfa(to_ast(shunting_yard(lexer(pattern))));

    file = fopen(file_path, "r");
    tmp_file = fopen("tmp.txt", "w");
    if(file == NULL || tmp_file == NULL)
        errx(EXIT_FAILURE, "cannot open the files.");

    while((len_line = getline(&line, &line_size, file)) != -1)
    {
        printf("----new line = %s; of length = %li-----\n",line,strlen(line));

        test = get_pattern(line, len_line, &len_pattern, a);
        while(test != -1)
        {
            position += test;
            start = position;
            end = start+len_word;
            position = end;

            printf("before replace: start = %i; end = %i; len_pattern = %li; line start = %s\n",start,end,len_pattern,&line[start]);

            insert_string(&line[start], new_word, len_pattern, len_word);

            printf("after replace: line start = %s\n",line);

            test = get_pattern(line+end, strlen(line+end), &len_pattern, a);
        }
        printf("-----line with all changes = %s-----\n",line);
        fputs(line, tmp_file);
        position = 0;
    }
    free(line);
    fclose(file);
    fclose(tmp_file);

    remove(file_path);
    rename("tmp.txt",file_path);
}

char* get_name(char* path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
        errx(EXIT_FAILURE, "Cannot open the file.");

    int d = fileno(file);
    if (d == -1)
        errx(EXIT_FAILURE, "Cannot get the file descriptor.");

    char name[256];
    if (fcntl(d, F_GETPATH, name) == -1)
        errx(EXIT_FAILURE, "CAnnot get the name of the file.");

    fclose(file);
    return name;
}

void insert_string(char* dest, char* new_word, size_t len_old_word, size_t len_new_word)
{
    size_t len_dest = strlen(dest);

    if (len_new_word >= len_old_word)
    {
        memmove(dest + len_new_word, dest + len_old_word, len_dest - len_old_word + 1);
        memcpy(dest, new_word, len_new_word);
    }

    else
    {
        size_t diff = len_old_word - len_new_word;
        size_t new_len_dest = len_dest - diff;

        memmove(dest + len_new_word, dest + len_old_word, new_len_dest - len_old_word + 2);
        memcpy(dest, new_word, len_new_word);
        dest[new_len_dest] = '\0';
    }
}

int get_pattern(char* line, ssize_t len_line, size_t* len_pattern, automaton* a)
{
    int position = 0;
    ssize_t i = 0;
    size_t j = 0;
    size_t len_word = 0;
    char word[len_line];
    while (i < len_line)
    {
        j = 0;
        len_word = 0;
        while(i < len_line && line[i] != ' ' && line[i] != '\n')
        {
            word[j] = line[i];
            ++j;
            ++i;
            ++len_word;
            //printf("word in loop: %s\n",word);
        }

        word[j] = 0;
        printf("word after loop: %s\n",word);

        if(accepts_word(a,get_origins(a),word))
        {
            printf("%s accepted\n",word);
            *len_pattern = len_word;
            return position;
        }

        ++i;
        position = (int)i;
        //printf("stuck here : %li; %li\n",i,len_line);
    }

    return -1;
}
*/
