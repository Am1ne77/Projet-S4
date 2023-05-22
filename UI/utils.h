#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
#define CHECK(widget)\
    if(widget == NULL) exit(1);

#include <gtk/gtk.h>
#include <string.h>
#include <gmodule.h>
#include <math.h>
#include "../Interpretor/interpretor.h"
#include "../replace/replace.h"

typedef struct Page
{
    GtkWindow *window;
    GtkButton *start_button;
    GtkButton *close_button;
    GtkImage *image_area;
    GtkTextView *fileView_area;
    GtkButton *execute_button;
    GtkEntry *command_entry;
    GtkEntry *word_entry;
    GtkButton *last_word;
    GtkButton *last_command;
    GtkButton *next_word;
    GtkButton *next_command;

   GtkFileChooserButton *file_input;
} Page;

typedef struct UserInterface
{
    GtkWindow *current_window;
    Page *first_page;
    Page *second_page;
    Page *third_page;
    GtkImage *image_area;
    GdkPixbuf *pixbuf;
    GtkEntry *command_entry;
    GtkEntry *word_entry;
    GtkButton *execute_button;
    GtkTextView *fileView_area;
    GtkFileChooserButton *file_input;
    vector *command_histo;
    vector *word_histo;
    size_t command_i;
    size_t word_i;
    GtkButton *last_word;
    GtkButton *last_command;
    GtkButton *next_word;
    GtkButton *next_command;
    gchar *filename; 
    guint event;

} UserInterface;

void initialise_text_view(GtkTextView *tv);

void start(GtkButton *button, gpointer user_data);

void close_window(GtkButton *button, gpointer user_data);

void execute(GtkButton *button, gpointer user_data);

void execute_file(gpointer user_data, char *regex, char *word);

void execute_language(gpointer user_data, char *regex, char *word);

void command(GtkButton *button, gpointer user_data);

void last_word(GtkButton *button, gpointer user_data);

void last_command(GtkButton *button, gpointer user_data);

void next_word(GtkButton *button, gpointer user_data);

void next_command(GtkButton *button, gpointer user_data);

void new_file(GtkButton *button, gpointer user_data);

void histo_sensi(gpointer user_data);

#endif
