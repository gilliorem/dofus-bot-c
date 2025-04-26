#include "mouse_manager.h"
#include <math.h>
#include <stdlib.h>
#include "types.h"
#include "screen_reading.h"

void	get_mouse_coordinates(WinManager *wm, Point point)
{
	Window root_return, child_return;
	int root_x_return, root_y_return;
	unsigned int mask_return;

	XSetInputFocus(wm->display,
		wm->root,
		RevertToPointerRoot,
		CurrentTime);

	XQueryPointer(wm->display,
		wm->root,
		&root_return,
		&child_return,
		&root_x_return,
		&root_y_return,
		&point.x,
		&point.y,
		&mask_return);

	printf("(x:%d, y:%d)", point.x, point.y);
	printf("\n");
	sleep(1);
}

void	move_mouse(WinManager *wm, int x, int y)
{
	XWarpPointer(wm->display, 
	None, 
	wm->root, 
	0, 0, 0, 0, x, y);
}

void fake_click(WinManager *wm, int button, Bool down)
{
	XTestFakeButtonEvent(wm->display, button, down, CurrentTime);
	XTestFakeButtonEvent(wm->display, button, False, CurrentTime);
	XSync(wm->display, False); 
}

void	click(WinManager *wm, int x, int y)
{
	move_mouse(wm, x, y);
	sleep(1);
	fake_click(wm, 1, True);
	sleep(1);
}

void	double_click(WinManager *wm, int x, int y)
{
	move_mouse(wm, x, y);
	fake_click(wm, 1, True);
	sleep(.1);
	fake_click(wm, 1, True);
}

