#include <gtk/gtk.h>
#include "utils.h"

int main(int argc, char** argv)
{
    //Initializes GTK.
    gtk_init(NULL, NULL);

    //Gets the widgets and check if it works.
    GtkBuilder *builder = 
        gtk_builder_new_from_file("ui.glade");
    CHECK(builder);

    //Widgets of first window.
    GtkButton *first_start_button = 
        GTK_BUTTON(gtk_builder_get_object(builder, "first_start_button"));
    CHECK(first_start_button);

    GtkButton *first_close_button =
        GTK_BUTTON(gtk_builder_get_object(builder, "first_close_button"));
    CHECK(first_close_button);

    GtkImage *first_image_area = 
        GTK_IMAGE(gtk_builder_get_object(builder, "first_image_area"));
    CHECK(first_image_area);

    GtkWindow *first_window = 
        GTK_WINDOW(gtk_builder_get_object(builder, "first_window"));
    CHECK(first_window);

    //Widgets of second window.
    GtkWindow *second_window = 
        GTK_WINDOW(gtk_builder_get_object(builder, "second_window"));
    CHECK(second_window);

    GtkButton *second_close_button = 
        GTK_BUTTON(gtk_builder_get_object(builder, "second_close_button"));
    CHECK(second_close_button);

    GtkFileChooserButton *second_fileInput_button = 
        GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "second_fileInput_button"));
    CHECK(second_fileInput_button);

    GtkEntry *second_command_entry = 
        GTK_ENTRY(gtk_builder_get_object(builder, "second_command_entry"));
    CHECK(second_command_entry);

    GtkButton *second_execute_button = 
        GTK_BUTTON(gtk_builder_get_object(builder, "second_execute_button"));
    CHECK(second_execute_button);

    GtkTextView *second_fileView_area = 
        GTK_TEXT_VIEW(gtk_builder_get_object(builder, "second_fileView_area"));
    CHECK(second_fileView_area);
    initialise_text_view(second_fileView_area);

    g_object_unref(builder);

    //Show window.
    gtk_widget_show_all(GTK_WIDGET(first_window));
    gtk_widget_hide(GTK_WIDGET(second_window));

    //Initializes the struct UserInterface.
    int height, width; 
    gtk_window_get_size(first_window, &width, &height);

    Page first_page = 
    {
        .window = first_window,
        .close_button = first_close_button,
        .start_button = first_start_button,
        .image_area = first_image_area,
    };

    Page second_page =
    {
        .window = second_window,
        .close_button = second_close_button,
        .execute_button = second_execute_button,
        .command_entry = second_command_entry,
        .fileView_area = second_fileView_area,
    };

    UserInterface ui = 
    {
        .first_page = &first_page,
        .second_page = &second_page,
    };


    //Connect event handlers.
    g_signal_connect(first_start_button, "clicked", G_CALLBACK(start), &ui);

    g_signal_connect(second_execute_button, "clicked", G_CALLBACK(execute), &ui);

    g_signal_connect(first_close_button, "clicked", G_CALLBACK(close_window), &ui);
    g_signal_connect(second_close_button, "clicked", G_CALLBACK(close_window), &ui);

    g_signal_connect(second_command_entry, "changed", G_CALLBACK(command), &ui);


    //Runs the main loop.
    gtk_main(); 

    //Exits.
    return 0;

}
