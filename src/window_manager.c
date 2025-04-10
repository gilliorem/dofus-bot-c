#include "types.h"
#include "window_manager.h"
#include <stdio.h> 
#include <stdlib.h>
#include <X11/Xlib.h> 
#include <string.h>
#include <X11/Xutil.h>

WinManager	*setXConnection(void)
{
	WinManager *wm = malloc(sizeof(WinManager));
	if(!wm) return NULL;

	wm->display = XOpenDisplay(NULL);
	if (!wm->display)
	{
		printf("Error making the X connection.\n");
		free(wm);
		return NULL;
	}
	else
		printf("X11 connection established.\n");
	wm->root = XDefaultRootWindow(wm->display);
	
	return (wm);
}
void 	get_window_name(WinManager *wm)
{
	Window root_return, parent_return;
	Window *children_return;
	unsigned int nchildren_return;
	XQueryTree(wm->display,
	wm->root,
	&root_return,
	&parent_return,
	&children_return,
	&nchildren_return);
	printf("numbers of windows : %d\n", nchildren_return);
	char *window_name_return;
	int counter = 0;
	for (int i = 0; i < nchildren_return; i++)
	{
		if (XFetchName(wm->display, children_return[i], &window_name_return))
		{
			printf("%s\n", window_name_return);
			if (strstr(window_name_return, "dofus-retro") != NULL)
				{
					counter++;
					wm->window = parent_return;
					printf("%s\n", window_name_return);
				}
		}
		else if (XFetchName(wm->display, children_return[i], &window_name_return)==0)
			printf("could not get the name of window %d\n", i);
	}
	printf("%d of %s window with the same name\n", counter, window_name_return);
	printf("..........\n");
}

void	get_subwindows(WinManager *wm)
{
	get_window_name(wm);
	Window root_return, parent_return;
	Window *children_return;
	unsigned int nchildren_return;
//	XQueryTree(wm->display, wm->window, &root_return, &parent_return, &children_return, &nchildren_return);

	printf("numbers of subwindows : %d\n", nchildren_return);
}


void get_attributes(WinManager *wm)
{
	XWindowAttributes root_window_attributes;
	XGetWindowAttributes(wm->display, wm->root, &root_window_attributes);
	XSetInputFocus(wm->display, wm->root, RevertToPointerRoot, CurrentTime);	
}
