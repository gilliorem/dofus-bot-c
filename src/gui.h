#ifndef GUI_H
#define GUI_H

#include "mouse_manager.h"
#include <gtk/gtk.h>
#include "log.h"
#include "window_manager.h"


int launch_gui(GtkApplication *app, WinManager *wm );

#endif
