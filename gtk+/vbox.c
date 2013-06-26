#include <gtk/gtk.h>

int
main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *settings;
    GtkWidget *accounts;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 250);
    gtk_window_set_title(GTK_WINDOW(window), "GtkVBox");
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    vbox = gtk_vbox_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    settings = gtk_button_new_with_label("Settings");
    accounts = gtk_button_new_with_label("Accounts");

    gtk_box_pack_end(GTK_BOX(vbox), settings, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), accounts, TRUE, TRUE, 0);
    
    g_signal_connect(window, "destroy",
            G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
