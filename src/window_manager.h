#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct 
{
	Display *display;
	Window root;
	Window specific_window;
	XWindowAttributes window_attributes;
	XEvent event;
} WinManager;

WinManager	*setXConnection(void);
void	get_window_name(WinManager *wm);
// TO DO : turn those 2 func into one using recursion.
void	get_subwindows(WinManager *wm);
void	get_attributes(WinManager *wm);

#endif
