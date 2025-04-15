#include <math.h>
#include <stdlib.h>
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

int	log_in(WinManager *wm)
{
	Rectangle orange_r = create_rectangle(1000, 650, 100, 20);
	XImage *orange_button_zone = get_zone_to_check(wm, orange_r);
	Rectangle log_r = create_rectangle(600, 500, 10, 10);
	XImage *log_zone = get_zone_to_check(wm, log_r);
	if (check_orange_color(orange_button_zone) == 1)
		click_orange_button(wm);
	else if (check_log_in(log_zone) == 1)
		click_log_button(wm);
	sleep(1);
	start(wm);
	return 0;
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

void open_inventory(WinManager *wm)
{
	move_mouse(wm, 1322, 886);
	sleep(1);
	fake_click(wm, 1, true);
	sleep(1);
}

void close_inventory(WinManager *wm)
{
	move_mouse(wm, 1629, 122);
	sleep(1);
	fake_click(wm, 1, true);
	sleep(1);
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

void	tactical_mode(WinManager *wm)
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

void	move_towards_enemy(WinManager *wm, Rgb color_matrix[1080][1920])
{
	Point player = find_player(mandrage_color_pattern, color_matrix, 2, 2);
	Point enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 10, 2);
	while (abs(player.x > enemy.x) > 50 || abs(player.y > enemy.y) > 50)
	{
		player = find_player(mandrage_color_pattern, color_matrix, 2, 2);
		enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 10, 2);
		if (abs(player.x - enemy.x) > 50)
		{
			if (player.x > enemy.x)
			{
				printf("PLAYER X IS SMALLER THAN ENEMY X : SO MOVE LEFT TO GET CLOSER TO ENEMY\n");
				move_left(wm, player);
				sleep(2);
				Point player_ = find_player(mandrage_color_pattern, color_matrix, 2, 2);
				if (player.x == player_.x)
				{
					printf("PLAYER COULD NOT MOVE LEFT. TRY TO MOVE UP AND LEFT\n");
					move_up_left(wm, player);
				}
				printf("Player has moved in (%d, %d)\n", player.x, player.y);
			}
			else if (player.x < enemy.x)
			{
				printf("PLAYER X IS BIGGER THAN ENEMY X : SO MOVE RIGHT TO GET CLOSER TO ENEMY\n");
				move_right(wm, player);
				sleep(2);
				Point player = find_player(mandrage_color_pattern, color_matrix, 2, 2);
				printf("Player has moved in (%d, %d)\n", player.x, player.y);
			}
		}
		if (abs(player.y - enemy.y) > 50)
		{
			if (player.y < enemy.y)
			{
				printf("PLAYER IS 'ABOVE' ENEMY: PLAYER MOVE DOWN TO GET CLOSER TO ENEMY\n");
				move_down(wm, player);
				sleep(2);
				Point player_ = find_player(mandrage_color_pattern, color_matrix, 2, 2);
			}
			else if (player.y > enemy.y)
			{
				printf("PLAYER IS 'BELOW' ENEMY: PLAYER MOVE UP TO GET CLOSER TO ENEMY\n");
				move_up(wm, player);
				sleep(2);
				Point player_ = find_player(mandrage_color_pattern, color_matrix, 2, 2);
				if (player.y == player_.y)
				{
					printf("PLAYER COULD NOT MOVE UP, WILL TRY TO MOVE RIGHT UP\n");
					move_up_right(wm, player);
				}
				printf("Player has moved in (%d, %d)\n", player.x, player.y);
			}
		}
	}
	printf("ENEMY IN RANGE: %dx %dy close\n", player.x - enemy.x, player.y - enemy.y);
}

int	check_orange_color_pods(WinManager *wm)
{
	Rectangle pods_zone = create_rectangle(1226, 482, 10, 4);
	XImage *pods_zone_image = get_zone_to_check(wm, pods_zone);
	int orange_counter = 0;
	int tolerance = 5;
	for (int i = 0; i < pods_zone.height ; i++)
	{
		for (int j = 0; j < pods_zone.width ; j++)
		{
			unsigned long pixel = XGetPixel(pods_zone_image, j, i);
			Rgb rgb = convert_pixel_to_rgb(pods_zone_image, pixel);
			if (abs(rgb.r - orange_button.r) < tolerance
			&& abs(rgb.g - orange_button.g) < tolerance
			&& abs(rgb.b - orange_button.b) < tolerance)
				orange_counter++;
		}
	}
	if (orange_counter > 5)
	{
		printf("FULL PODS\n");
		return 1;
	}
	else
	{
		printf("pas encore full pods\n");
	}
	return 0;
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

