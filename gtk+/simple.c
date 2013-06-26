#include <gtk/gtk.h>

int
main(int argc, char *argv[])
{
    GtkWidget *window;

    gtk_init(&argc, &argv);

    // GtkWindowType
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "center");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 250);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Subscribe to the destroy signal
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);

    // Display the window
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
