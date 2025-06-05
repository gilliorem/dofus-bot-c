#include "gui.h"
#include "window_manager.h"
static int init_gtk();

static int init_gtk()
{
	GtkApplication *app;
	int status;
	app = gtk_application_new("dofus.gtk.ui", 0);
	g_signal_connect (app, "activate", G_CALLBACK (launch_gui), NULL);
}
