#include <stdio.h>
#include <stdlib.h>
#include "window_manager.h"
#include "screen_reading.h"
#include "log.h"
#include "mouse_manager.h"
#include "farmer.h"
#include "combat.h"
#include "types.h"
#include "bot.h"
#include "gui.h"
#include "movement.h"

WinManager *wm = NULL;
GtkApplication *app = NULL;
WinManager* get_wm()
{
	return (wm);
}

GtkApplication *get_gtk_app()
{
	return (app);
}

static void on_activate(GtkApplication *app, gpointer user_data)
{
    WinManager *wm = (WinManager *)user_data;
    launch_gui(app, wm);
}

int	init_gtk(WinManager *wm)
{
    GtkApplication *app = gtk_application_new("dofus.gtk.ui", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), wm);
    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);
    return status;
}

int 	main()
{
	wm = init_bot();
	check_ready_button(wm);

	return 0;
}

