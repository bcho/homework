#include <gtk/gtk.h>

gint count = 0;

void
cb_inc(GtkWidget *widget, gpointer label)
{
    char buf[5];

    count = count + 1;
    sprintf(buf, "%d", count);
    gtk_label_set_text(label, buf);
}

void
cb_dec(GtkWidget *widget, gpointer label)
{
    char buf[5];

    count = count - 1;
    sprintf(buf, "%d", count);
    gtk_label_set_text(label, buf);
}

int
main(int argc, char **argv)
{
    GtkWidget *label;
    GtkWidget *window;
    GtkWidget *frame;
    GtkWidget *btn_plus;
    GtkWidget *btn_minus;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 250);
    gtk_window_set_title(GTK_WINDOW(window), "+-");

    frame = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), frame);

    btn_plus = gtk_button_new_with_label("+");
    gtk_widget_set_size_request(btn_plus, 80, 35);
    gtk_fixed_put(GTK_FIXED(frame), btn_plus, 50, 20);

    btn_minus = gtk_button_new_with_label("-");
    gtk_widget_set_size_request(btn_minus, 80, 35);
    gtk_fixed_put(GTK_FIXED(frame), btn_minus, 50, 75);

    label = gtk_label_new("0");
    gtk_fixed_put(GTK_FIXED(frame), label, 190, 58);

    gtk_widget_show_all(window);

    g_signal_connect(window, "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
    // bind to click event
    g_signal_connect(btn_plus, "clicked",
            G_CALLBACK(cb_inc), label);
    g_signal_connect(btn_minus, "clicked",
            G_CALLBACK(cb_dec), label);

    gtk_main();

    return 0;
}
