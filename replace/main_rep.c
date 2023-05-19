#include "interpretor.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL;
    size_t line_size = 0;
    ssize_t len_line;
    size_t len_pattern = 0;
    const char *pattern = argv[1];
    const char *new_word = argv[2];

    // Ouvrir le fichier en lecture/écriture
    file = fopen("test.txt", "r+");

    if (file == NULL)
        errx(EXIT_FAILURE,"Error opening the file");

    // Lire le fichier ligne par ligne
    while ((len_line = getline(&line, &line_size, file)) != -1) 
    {
        // Recherche du mot à remplacer dans la ligne
        char *position = get_pattern(line, len_line, pattern, &len_pattern);

        while (position != NULL) {
            // Calculer l'index de début et de fin du mot à remplacer
            int start = position - line;
            int end = start + len_pattern;

            // Remplacer le mot
            strncpy(&line[start], new_word, strlen(nouveau_mot));

            // Chercher la prochaine occurrence du mot
            position = get_pattern(line+end, pattern, &len_pattern);
        }

        // Réécrire la ligne modifiée dans le fichier
        fseek(file, -len_line, SEEK_CUR);
        fputs(line, file);
    }

    // Libérer la mémoire allouée
    free(ligne);

    // Fermer le fichier
    fclose(fichier);

    return 0;
}

char* get_pattern(line, len_line, pattern, &len_pattern)
{
    char *position = 0;
    automaton* a = create_dfa(to_ast(shunting_yard(lexer(pattern))));
    size_t i = 0;
    size_t j = 0;
    size_t len_word = 0;
    char word[len_line];
    while (i < len_line)
    {
        while(line[i] != " ")
        {
            j = 0;
            word[j] = line[i];
            ++j;
            ++i;
            ++len_word;
        }
        word[j] = 0;

        if(accepts_word(a,get_origines(a),word))
        {
            len_pattern = len_word;
            return position;
        }

        position = i;
        ++i;
    }

    return NULL;
}

