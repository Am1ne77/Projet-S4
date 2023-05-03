#include "utils.h"

//Set values of struct UserInterface with the current window value.
void new_window(Page *newpage, gpointer user_data)
{
    UserInterface *ui = user_data;

    //ui->fileInput_button = newpage->fileInput_button;
    ui->current_window = newpage->window;
    ui->fileView_area = newpage->fileView_area;
    ui->execute_button = newpage->execute_button;
    ui->command_entry = newpage->command_entry;
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

    if(strcmp(gtk_entry_get_text(ui->command_entry), "") == 0)
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
    
    /*
    if (ui->event == 0)
    {
        ui->event = g_timeout_add(500, sensitive, ui);
        ui->event = g_timeout_add(500, sensitive, ui);
    }

    else
    {
        g_source_remove(ui->event);
        ui->event = 0;
    }*/
}

void close_window(GtkButton *button __attribute__((unused)),
        gpointer user_data __attribute__((unused)))
{
    gtk_main_quit();
}

void execute(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    UserInterface *ui = user_data;
    const gchar *command = gtk_entry_get_text(ui->command_entry);

    char *argv = g_strdup(command);

    GtkTextBuffer *buf;
    buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (ui->fileView_area));

    char *regex = strtok(argv, " ");
    char *word = strtok(NULL, " ");
   
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
    gtk_entry_set_text(ui->command_entry, "");
}

void command(GtkButton *button __attribute__((unused)), gpointer user_data)
{
    sensitive(user_data);
}

