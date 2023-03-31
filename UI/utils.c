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

void start(GtkButton *button, gpointer user_data)
{
    UserInterface *ui = user_data;

    new_window(ui->second_page, user_data); 

    gtk_widget_hide(GTK_WIDGET(ui->first_page->window));
    gtk_widget_show_all(GTK_WIDGET(ui->current_window));

    
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

void close_window(GtkButton *button, gpointer user_data)
{
    gtk_main_quit();
}

void execute(GtkButton *button, gpointer user_data)
{
    UserInterface *ui = user_data;
    const gchar *command = gtk_entry_get_text(ui->command_entry);
    GtkTextBuffer *buf;
    buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (ui->fileView_area));
    gtk_text_buffer_set_text(buf, command, -1);
    gtk_entry_set_text(ui->command_entry, "");
}

