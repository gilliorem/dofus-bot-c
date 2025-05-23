#include "gui.h"
#include "window_manager.h"
static int init_gtk();

static void on_login_button_clicked(GtkWidget *widget, gpointer data)
{
    printf("button clicked\n");
    log_in(get_wm()); 
}

int launch_gui(GtkApplication *app, WinManager *wm)
{

    init_gtk();
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    //window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    window = gtk_application_window_new (app);
    gtk_window_set_title(GTK_WINDOW(window), "Dofus Bot Login");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
    
    grid = gtk_grid_new();

    gtk_container_add (GTK_CONTAINER (window), grid);

    button = gtk_button_new_with_label("Log in");
    g_signal_connect(button, "clicked", G_CALLBACK(on_login_button_clicked), NULL);

    gtk_grid_attach(GTK_GRID (grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    // why swapped ?

    gtk_grid_attach(GTK_GRID (grid), button, 1, 0, 1, 1);

//    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window);
 //   gtk_main(); // boucle principale GTK ?

    return 0;
}

static int	init_gtk()
{
    GtkApplication *app;
    int	status;
    app = gtk_application_new ("dofus.gtk.ui", 0);
    g_signal_connect (app, "activate", G_CALLBACK (launch_gui), NULL);
    status = g_application_run (G_APPLICATION (app), 0, NULL);
    g_object_unref (app);

    return status;
}
