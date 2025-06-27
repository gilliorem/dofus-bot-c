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

// wrapper appelé quand GTK est activé
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
	Rectangle zone = create_rectangle(1920/2,1080/2,100,100);
	XImage *img = get_zone_to_check(wm, zone);
	check_color_pattern(wm, context_menu_light_gray, img, 3);
	//ready_button_visible(wm);
	//    init_gtk(wm);

	//reap_wheat(wm);
	// check_hammer_zone(wm);
	//check_state(wm);
	
	return 0;
}

