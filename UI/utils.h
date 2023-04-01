#ifndef UTILS_H
#define UTILS_H
#define CHECK(widget)\
    if(widget == NULL) exit(1);

#include <gtk/gtk.h>
#include <string.h>
#include <gmodule.h>
#include "../Interpretor/interpretor.h"

typedef struct Page
{
    GtkWindow *window;
    GtkButton *start_button;
    GtkButton *close_button;
    GtkImage *image_area;
    GtkTextView *fileView_area;
    GtkButton *execute_button;
    GtkEntry *command_entry;
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
    GtkButton *execute_button;
    GtkTextView *fileView_area;
    guint event;

} UserInterface;

void initialise_text_view(GtkTextView *tv);

void start(GtkButton *button, gpointer user_data);

void close_window(GtkButton *button, gpointer user_data);

void execute(GtkButton *button, gpointer user_data);

void command(GtkButton *button, gpointer user_data);

#endif
