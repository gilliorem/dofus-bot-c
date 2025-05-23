#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "types.h"

WinManager	*get_wm(void);
WinManager	*setXConnection(void);
WinManager	*init_bot(void);
void	get_window_name(WinManager *wm);
// TO DO : turn those 2 func into one using recursion.
void	get_subwindows(WinManager *wm);
void	get_attributes(WinManager *wm);

#endif
