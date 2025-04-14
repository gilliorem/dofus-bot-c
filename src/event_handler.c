#include <math.h>
#include "types.h"
#include "event_handler.h"
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
	XWarpPointer(wm->display, None, wm->root, 0, 0, 0, 0, x, y);
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
	fake_click(wm, 1, True);
}

void	double_click(WinManager *wm)
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
	move_mouse(wm, 544, 530);
	int i = 0;
	while (i < 3)
	{
		double_click(wm);
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
	sleep(1);
	fake_click(wm, 1, True);
	sleep(1);
	move_mouse(wm, x+=50, y+=70);
	sleep(1);
	fake_click(wm, 1, True);
	sleep(15);
}

void	equip_weapon(WinManager *wm)
{
	move_mouse(wm, 1340, 975);
	sleep(.5);
	double_click(wm);
}

void	equip_faux(WinManager *wm)
{
	move_mouse(wm, 1285, 975);
	sleep(.5);
	double_click(wm);
}

void	tactical_mode()
{
	move_mouse(wm, 1500, 760);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	place_player(WinManager *wm, Point placement)
{
	move_mouse(wm, placement.x, placement.y);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	move_right(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x + 100, player_pos.y);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	move_left(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x - 100, player_pos.y);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	move_up(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x, player_pos.y - 50);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	move_down(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x, player_pos.y + 50);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	move_down_left(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x - 125, player_pos.y + 75);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	move_up_right(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x + 100, player_pos.y - 75);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	move_up_left(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x - 100, player_pos.y - 75);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	boost(WinManager *wm, Point player)
{
	click(wm, 1440, 975);
	click(wm, player.x, player.y);
	sleep(1);
	click(wm, 1590, 975);
	click(wm, player.x, player.y);
}

void	attack(WinManager *wm, Point enemy)
{
	click(wm, 1390, 975);
	click(wm, enemy.x, enemy.y);
	sleep(2);
}
