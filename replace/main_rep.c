#include "../Interpretor/interpretor.h"
#include "main_rep.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
        errx(EXIT_FAILURE,"failure");

    FILE *file;
    char *line = NULL;
    size_t line_size = 0;
    ssize_t len_line;
    size_t len_pattern = 0;
    char *pattern = argv[1];
    char *new_word = argv[2];
    size_t len_word = strlen(new_word);
    int position;
    int test = 0;

    // Ouvrir le fichier en lecture/écriture
    file = fopen("test.txt", "r+");

    if (file == NULL)
        errx(EXIT_FAILURE,"Error opening the file");

    // Lire le fichier ligne par ligne
    while ((len_line = getline(&line, &line_size, file)) != -1) 
    {
        printf("new line = %s\n",&line[0]);
        // Recherche du mot à remplacer dans la ligne
        test = get_pattern(line, len_line, pattern, &len_pattern);
        while (test != -1) 
        {
            position += test;
            // Calculer l'index de début et de fin du mot à remplacer
            int start = position;
            int end = start + len_word;
            position = end;

            printf("before replace: start = %i; end = %i; len_pattern = %li; line start = %s\n",start,end,len_pattern,&line[start]);
            // Remplacer le mot
            insert_string(&line[start], new_word, len_pattern, len_word);

            printf("after replace: line start = %s\n",&line[start]);
            // Chercher la prochaine occurrence du mot
            test = get_pattern(line+end, len_line - position, pattern, &len_pattern);
        }

        // Réécrire la ligne modifiée dans le fichier
        fseek(file, -len_line, SEEK_CUR);
        fputs(line, file);
        printf("end line---------------------------------\n");
    }

    // Libérer la mémoire allouée
    free(line);

    // Fermer le fichier
    fclose(file);

    return 0;
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

        memmove(dest + len_new_word, dest + len_old_word, new_len_dest - len_old_word + 1);
        memcpy(dest, new_word, len_new_word);
        dest[new_len_dest] = '\0';
    }
}

int get_pattern(char* line, ssize_t len_line, char* pattern, size_t* len_pattern)
{
    int position = 0;
    automaton* a = create_dfa(to_ast(shunting_yard(lexer(pattern))));
    ssize_t i = 0;
    size_t j = 0;
    size_t len_word = 0;
    char word[len_line];
    while (i < len_line)
    {
        //printf("word before loop : %s\n",word);
        j = 0;
        len_word = 0;
        while(i < len_line && line[i] != ' ')
        {
            word[j] = line[i];
            ++j;
            ++i;
            ++len_word;
            //printf("word in loop: %s\n",word);
        }
        /*
        if(i == len_line)
            return -1;
*/
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
        printf("stuck here : %li; %li\n",i,len_line);
    }

    return -1;
}

