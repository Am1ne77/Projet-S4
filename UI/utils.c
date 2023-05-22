#include "utils.h"

//Set values of struct UserInterface with the current window value.
void new_window(Page *newpage, gpointer user_data)
{
    UserInterface *ui = user_data;

    ui->current_window = newpage->window;
    ui->fileView_area = newpage->fileView_area;
    ui->execute_button = newpage->execute_button;
    ui->command_entry = newpage->command_entry;
    ui->word_entry = newpage->word_entry;
    ui->file_input = newpage->file_input;
    ui->last_word = newpage->last_word;
    ui->last_command = newpage->last_command;
    ui->next_word = newpage->next_word;
    ui->next_command = newpage->next_command;
}

void initialise_text_view(GtkTextView *tv)
{
    gtk_text_view_set_editable(tv, FALSE);
    gtk_text_view_set_cursor_visible(tv, FALSE);
    gtk_text_view_set_top_margin(tv, 10);
    gtk_text_view_set_left_margin(tv, 10);
}

gboolean sensitive(gpointer user_data)
{
    UserInterface *ui = user_data;

    if(strcmp(gtk_entry_get_text(ui->command_entry), "") == 0 ||
    strcmp(gtk_entry_get_text(ui->word_entry), "") == 0) 
    {
        gtk_widget_set_sensitive(GTK_WIDGET(ui->execute_button), FALSE);
    }
    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(ui->execute_button), TRUE);
    }
    return TRUE;
}

void start(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    UserInterface *ui = user_data;

    new_window(ui->second_page, user_data); 

    gtk_widget_hide(GTK_WIDGET(ui->first_page->window));
    gtk_widget_show_all(GTK_WIDGET(ui->current_window));

    sensitive(user_data);
    
}

void close_window(GtkButton *button __attribute__((unused)),
        gpointer user_data __attribute__((unused)))
{
    gtk_main_quit();
}

void execute(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    UserInterface *ui = user_data;
    ui->filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->file_input));

    char *regex = malloc(2);
    strcpy(regex, (char*) gtk_entry_get_text(ui->command_entry));
    vector_pop(ui->command_histo, NULL);
    vector_push(ui->command_histo, regex);

    char *word = malloc(2);
    strcpy(word, (char*) gtk_entry_get_text(ui->word_entry));
    vector_pop(ui->word_histo, NULL);
    vector_push(ui->word_histo, word);

    ui->word_i++;
    ui->command_i++;

    if(ui->filename == NULL)
        execute_language(user_data, regex, word);
    else
        execute_file(user_data, regex, word);

    gtk_entry_set_text(ui->command_entry, "");
    gtk_entry_set_text(ui->word_entry, "");
    gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(ui->file_input));

    vector_push(ui->word_histo, "");
    vector_push(ui->command_histo, "");

    ui->word_i = ui->word_histo->size-1;
    ui->command_i = ui->command_histo->size-1;

    gtk_widget_set_sensitive(GTK_WIDGET(ui->next_word), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(ui->next_command), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(ui->last_word), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(ui->last_command), TRUE);

}

void execute_file(gpointer user_data, char *regex, char *word)
{
    UserInterface *ui = user_data;

    GtkTextBuffer *buf;
    buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (ui->fileView_area));

    gchar* contents = NULL;
    gsize length = 0;
    GError* error = NULL;

    display(find(ui->filename, regex, DELIM));
    replace(ui->filename, regex, word, DELIM);
    g_file_get_contents(ui->filename, &contents, &length, &error);

    gtk_text_buffer_set_text(buf, contents, -1);

}


void execute_language(gpointer user_data, char *regex, char *word)
{
    UserInterface *ui = user_data;

    GtkTextBuffer *buf;
    buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (ui->fileView_area));

   
    Array *arr = lexer(regex);
    Stack *s = shunting_yard(arr);
    btree *ast = to_ast(s);
    automaton *a = create_dfa(ast);
    char* origins = get_origins(a);
    int res = accepts_word(a, origins, word);
   
    char *str = res == 1? "is accepted" : 
        "is not accepted";
    
    char *r;
    asprintf(&r, "The word \"%s\" %s in the language \"%s\"\n", word, str, regex);
   
    gtk_text_buffer_set_text(buf, r, -1);
}

void command(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    sensitive(user_data);
}

void last_word(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    UserInterface *ui = user_data;
    ui->word_i--;
    histo_sensi(user_data);
    gtk_entry_set_text(ui->word_entry, ui->word_histo->data[ui->word_i]);
}

void last_command(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    UserInterface *ui = user_data;
    ui->command_i--;
    histo_sensi(user_data);
    gtk_entry_set_text(ui->command_entry, ui->command_histo->data[ui->command_i]);
}
    
void next_word(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    UserInterface *ui = user_data;
    ui->word_i++;
    histo_sensi(user_data);
    gtk_entry_set_text(ui->word_entry, ui->word_histo->data[ui->word_i]);
}

void next_command(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    UserInterface *ui = user_data;
    ui->command_i++;
    histo_sensi(user_data);
    gtk_entry_set_text(ui->command_entry, ui->command_histo->data[ui->command_i]);
}


void new_file(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    UserInterface *ui = user_data;
    ui->filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->file_input));


    GtkTextBuffer *buf;
    buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (ui->fileView_area));

    gchar* contents = NULL;
    gsize length = 0;
    GError* error = NULL;


    g_file_get_contents(ui->filename, &contents, &length, &error);

    gtk_text_buffer_set_text(buf, contents, -1);

}


void histo_sensi(gpointer user_data)
{
    UserInterface *ui = user_data;

    if(ui->word_i == 0)
    {
        if(ui->word_histo->size == 2) 
            gtk_widget_set_sensitive(GTK_WIDGET(ui->next_word), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(ui->last_word), FALSE);
    }

    else if(ui->word_i >= ui->word_histo->size-1)
    {
        if(ui->word_histo->size == 2) 
            gtk_widget_set_sensitive(GTK_WIDGET(ui->last_word), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(ui->next_word), FALSE);
    }

    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(ui->last_word), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(ui->next_word), TRUE);
    }

    if(ui->command_i == 0)
    {
        if(ui->command_histo->size == 2) 
            gtk_widget_set_sensitive(GTK_WIDGET(ui->next_command), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(ui->last_command), FALSE);
    }


    else if(ui->command_i >= ui->command_histo->size-1)
    {
        if(ui->command_histo->size == 2) 
            gtk_widget_set_sensitive(GTK_WIDGET(ui->last_command), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(ui->next_command), FALSE);
    }

    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(ui->last_command), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(ui->next_command), TRUE);
    }
}
