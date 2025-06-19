#include "gui.h"

//static int init_gtk();

static void on_login_button_clicked(GtkWidget *widget, gpointer data)
{
    printf("button clicked\n");
    log_in(get_wm()); 
}

void reap_wheat_cb(GtkWidget *widget, gpointer data)
{
    WinManager *wm = get_wm(); // tu te débrouilles avec un singleton ou une globale
    Rgb (*matrix)[1080] = get_screen_matrix_v(); // à adapter selon ton archi

    if (!wm || !matrix)
    {
        g_print("Wheat callback failed: missing wm or matrix\n");
        return;
    }
    reap_wheat(wm);
}

void reap_barley_cb(GtkWidget *widget, gpointer data)
{
    WinManager *wm = get_wm(); // tu te débrouilles avec un singleton ou une globale
    Rgb (*matrix)[1920] = get_screen_matrix(); // à adapter selon ton archi

    if (!wm || !matrix)
    {
        g_print("Wheat callback failed: missing wm or matrix\n");
        return;
    }
    reap_barley(wm, matrix);
}

void reap_oat_cb(GtkWidget *widget, gpointer data)
{
    WinManager *wm = get_wm(); // tu te débrouilles avec un singleton ou une globale
    Rgb (*matrix)[1920] = get_screen_matrix(); // à adapter selon ton archi

    if (!wm || !matrix)
    {
        g_print("Wheat callback failed: missing wm or matrix\n");
        return;
    }
    reap_oat(wm, matrix);
}

void reap_hop_cb(GtkWidget *widget, gpointer data)
{
    WinManager *wm = get_wm(); // tu te débrouilles avec un singleton ou une globale
    Rgb (*matrix)[1920] = get_screen_matrix(); // à adapter selon ton archi

    if (!wm || !matrix)
    {
        g_print("Wheat callback failed: missing wm or matrix\n");
        return;
    }
    reap_hop(wm);
}

void reap_flax_cb(GtkWidget *widget, gpointer data)
{
    WinManager *wm = get_wm(); // tu te débrouilles avec un singleton ou une globale
    Rgb (*matrix)[1920] = get_screen_matrix(); // à adapter selon ton archi

    if (!wm || !matrix)
    {
        g_print("Wheat callback failed: missing wm or matrix\n");
        return;
    }
    reap_flax(wm);
}

void callback_field(GtkWidget *widget, gpointer data)
{
	field(get_wm());
}

void callback_log_in(GtkWidget *widget, gpointer data)
{
	log_in(get_wm());
}

void callback_character_screen(GtkWidget *widget, gpointer data)
{
	character_screen(get_wm());
}

void callback_bank(GtkWidget *widget, gpointer data)
{
	bank(get_wm());
}

void callback_quit(GtkWidget *widget, gpointer data)
{
	g_print("Quiting app..\n");
	gtk_main_quit();
}

GtkWidget *create_menu_with_items(const char *menu_title, const char **item_labels, void (**callbacks)(GtkWidget*, gpointer), int count)
{
    // Crée l'élément principal du menu (ex: "Farm")
    GtkWidget *menu_item = gtk_menu_item_new_with_label(menu_title);
    GtkWidget *submenu = gtk_menu_new();

    // Pour chaque sous-option du menu (Wheat, Barley, etc.)
    for (int i = 0; i < count; i++)
    {
        GtkWidget *item = gtk_menu_item_new_with_label(item_labels[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(submenu), item);

        if (callbacks[i])
            g_signal_connect(item, "activate", G_CALLBACK(callbacks[i]), NULL);
    }

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), submenu);
    return menu_item;
}

// Fonction appelée par g_application_run → elle construit l’UI
int launch_gui(GtkApplication *app, WinManager *wm)
{
    // Crée la fenêtre principa
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Dofus Bot");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);

    // Crée la barre de menu principale
    GtkWidget *menu_bar = gtk_menu_bar_new();

    // ----------- MENU FARM -----------
    const char *farm_items[] = {"Wheat", "Barley", "Oat", "Hop", "Flax"};
    void (*farm_callbacks[])(GtkWidget*, gpointer) = {
        reap_wheat_cb, reap_barley_cb, reap_oat_cb, reap_hop_cb, reap_flax_cb };
    GtkWidget *farm_menu = create_menu_with_items("Farm", farm_items, farm_callbacks, 5);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), farm_menu);

    // ----------- MENU LOGIN -----------
    const char *login_items[] = {"Character screen", "In Game"};
    void (*login_callbacks[])(GtkWidget*, gpointer) = {
        callback_character_screen, callback_log_in
    };
    GtkWidget *login_menu = create_menu_with_items("Login", login_items, login_callbacks, 2);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), login_menu);

    // ----------- MENU MAP -----------
    const char *move_items[] = {"field", "Bank"};
    void (*move_callbacks[])(GtkWidget*, gpointer) = {
        callback_field, callback_bank
    };
    GtkWidget *move_menu = create_menu_with_items("Move Map", move_items, move_callbacks, 2);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), move_menu);

    // ----------- Quit Menu
    const char* file_item[] = {"Quit"};
    void (*file_callbacks[])(GtkWidget*, gpointer) = {callback_quit};

    GtkWidget *file_menu = create_menu_with_items("Quit", file_item, file_callbacks, 1);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_menu);
    // ----------- AJOUT DANS LA FENÊTRE -----------
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Affiche tous les widgets
    gtk_widget_show_all(window);

    return 0;
}

static int	init_gtk()
{
    GtkApplication *app;
    int	status;
    app = gtk_application_new ("dofus.gtk.ui", 0);
    g_signal_connect (app, "activate", G_CALLBACK (create_menu_with_items), NULL);
    status = g_application_run (G_APPLICATION (app), 0, NULL);
    g_object_unref (app);

    return status;
}
