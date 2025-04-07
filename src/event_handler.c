#include <math.h>
#include "event_handler.h"

void	get_mouse_coordinates(WinManager *wm, Point *point)
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
	&point->x,
	&point->y,
	&mask_return);

	printf("(x:%d, y:%d)", point->x, point->y);
	printf("\n");
	sleep(1);
}

void	move_mouse(WinManager *wm, int x, int y)
{
	XWarpPointer(wm->display, None, wm->root, 0, 0, 0, 0, x, y);
}

void fake_click(WinManager *wm, int button, Bool down)
{
	XTestFakeButtonEvent(wm->display, button, down, CurrentTime);
	sleep(.1);
	XTestFakeButtonEvent(wm->display, button, False, CurrentTime);
	XSync(wm->display, False);
}

void	double_clic(WinManager *wm)
{
	fake_click(wm, 1, True);
	sleep(.1);
	fake_click(wm, 1, True);
}

void	click_log_button(WinManager *wm)
{
	move_mouse(wm, 544, 530);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	start(WinManager *wm)
{
	int i = 0;
	while (i < 3)
	{
		double_clic(wm);
		sleep(4);
		i++;
	}
}

void	click_orange_button(WinManager *wm)
{
	move_mouse(wm, 1000, 650);
	fake_click(wm, 1, True);
}

void	reap_wheat(WinManager* wm, int x, int y)
{
	move_mouse(wm, x, y);
	fake_click(wm, 1, True);
	sleep(.2);
	move_mouse(wm, x+=50, y+=70);
	sleep(.2);
	fake_click(wm, 1, True);
}


