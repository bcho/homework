#include <gtk/gtk.h>

void
cb_move(GtkWindow *window, GdkEvent *event, gpointer data)
{
    int x, y;
    char buf[10];

    x = event->configure.x;
    y = event->configure.y;
    sprintf(buf, "%d, %d", x, y);
    gtk_window_set_title(window, buf);
    g_print("%s", buf);
}

int
main(int argc, char *argv[])
{
    GtkWidget *window;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 250);
    gtk_widget_add_events(GTK_WIDGET(window), GDK_CONFIGURE);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    g_signal_connect(G_OBJECT(window), "configure-event",
            G_CALLBACK(cb_move), NULL);

    gtk_widget_show(window);

    gtk_main();

    return 0;
}
