#include "utils.h"
#include "sys/stat.h"

int main()
{
    mkdir("bin", 0777);

    //Initializes GTK.
    gtk_init(NULL, NULL);

    //Gets the widgets and check if it works.
    GtkBuilder *builder = 
        gtk_builder_new_from_file("./UI/ui.glade");
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

    GtkButton *second_last_command = 
        GTK_BUTTON(gtk_builder_get_object(builder, "second_last_command"));
    CHECK(second_last_command);

    GtkButton *second_next_command = 
        GTK_BUTTON(gtk_builder_get_object(builder, "second_next_command"));
    CHECK(second_next_command);

    GtkButton *second_last_word = 
        GTK_BUTTON(gtk_builder_get_object(builder, "second_last_word"));
    CHECK(second_last_word);

    GtkButton *second_next_word = 
        GTK_BUTTON(gtk_builder_get_object(builder, "second_next_word"));
    CHECK(second_next_word);

    GtkToggleButton *second_find = 
        GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "second_find_toggleButton"));
    CHECK(second_find);

    GtkToggleButton *second_replace = 
        GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "second_replace_toggleButton"));
    CHECK(second_replace);

    GtkFileChooserButton *second_fileInput_button = 
        GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "second_fileInput_button"));
    CHECK(second_fileInput_button);

    GtkEntry *second_command_entry = 
        GTK_ENTRY(gtk_builder_get_object(builder, "second_command_entry"));
    CHECK(second_command_entry);

    GtkEntry *second_word_entry = 
        GTK_ENTRY(gtk_builder_get_object(builder, "second_word_entry"));
    CHECK(second_word_entry);

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
        .word_entry = second_word_entry,
        .fileView_area = second_fileView_area,
        .file_input = second_fileInput_button,
        .last_word = second_last_word,
        .last_command = second_last_command,
        .next_word = second_next_word,
        .next_command = second_next_command,
        .find_button = second_find,
        .replace_button = second_replace,
    };

    UserInterface ui = 
    {
        .first_page = &first_page,
        .second_page = &second_page,
        .command_histo = vector_new(),
        .word_histo = vector_new(),
        .command_i = 0,
        .word_i = 0,
    };


    gtk_widget_set_sensitive(GTK_WIDGET(second_page.next_word), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(second_page.next_command), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(second_page.last_word), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(second_page.last_command), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(second_page.find_button), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(second_page.replace_button), FALSE);

    //Connect event handlers.
    g_signal_connect(first_start_button, "clicked", G_CALLBACK(start), &ui);

    g_signal_connect(second_execute_button, "clicked", G_CALLBACK(execute), &ui);

    g_signal_connect(first_close_button, "clicked", G_CALLBACK(close_window), &ui);
    g_signal_connect(second_close_button, "clicked", G_CALLBACK(close_window), &ui);

    g_signal_connect(second_fileInput_button, "file-set", G_CALLBACK(new_file), &ui);

    g_signal_connect(second_command_entry, "changed", G_CALLBACK(command), &ui);
    g_signal_connect(second_word_entry, "changed", G_CALLBACK(command), &ui);

    g_signal_connect(second_find, "toggled", G_CALLBACK(find_fct), &ui);
    g_signal_connect(second_replace, "toggled", G_CALLBACK(replace_fct), &ui);

    g_signal_connect(second_next_word, "clicked", G_CALLBACK(next_word), &ui);
    g_signal_connect(second_next_command, "clicked", G_CALLBACK(next_command), &ui);
    g_signal_connect(second_last_word, "clicked", G_CALLBACK(last_word), &ui);
    g_signal_connect(second_last_command, "clicked", G_CALLBACK(last_command), &ui);

    //Runs the main loop.
    gtk_main(); 

    //Exits.
    return 0;

}
