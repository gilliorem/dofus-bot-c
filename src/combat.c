#include "mouse_manager.h"
#include <math.h>
#include <stdlib.h>
#include "types.h"

//ajouter un check pour voir si l'arme est deja equipee
int	check_weapon(WinManager *wm)
{
	Rgb ref = {.r = 255, .g = 255, .b = 255};
	int tolerance = 5;
	Rectangle weapon_zone = create_rectangle(1274, 968, 1, 1);
	XImage *weapon_image = get_zone_to_check(wm, weapon_zone);
	printf("%d\n", weapon_image->height);
	unsigned long pixel = XGetPixel(weapon_image, 1, 1);
	Rgb weapon_color = convert_pixel_to_rgb(weapon_image, pixel);
	if (abs(ref.r - weapon_color.r) > tolerance)
		{
			printf("Faux is not equip\n");
			return 1;
		}
	printf("Faux is equiped\n");
	return 0;
}

void	equip_weapon(WinManager *wm)
{
	if (check_weapon(wm) == 0)
		return;
	move_mouse(wm, 1340, 975);
	sleep(.5);
	double_click(wm);
}

// in order to check if still in combat mode can check the pixel in 1080, 1025 (white flage)

int	check_tactical_mode(WinManager *wm)
{
	Rgb ref = {.r = 0, .g = 153, .b = 0};
	int tolerance = 5;
	Rectangle tactical_zone = create_rectangle(1533, 754, 1, 1);
	XImage *tactical_image = get_zone_to_check(wm, tactical_zone);
	Rgb* tactical_color = get_color_in_frame(wm, tactical_image);
	if (abs(ref.r - tactical_color->r) > tolerance)
		{
			printf("Tactical mode is OFF.\n");
			return 1;
		}
	printf("Tactical mode is ON\n");
	return 0;
}

void	tactical_mode(WinManager *wm)
{
	if (check_tactical_mode(wm) == 0)
		return;
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

void	click_ready_button(WinManager *wm)
{
	click(wm, 1575, 807);
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

int	move_towards_enemy(WinManager *wm, Rgb color_matrix[1080][1920])
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
				sleep(2);
				printf("Player has moved in (%d, %d)\n", player.x, player.y);
				click(wm, 1200, 1040);
				sleep(15);
			}
			else if (player.x < enemy.x)
			{
				printf("PLAYER X IS BIGGER THAN ENEMY X : SO MOVE RIGHT TO GET CLOSER TO ENEMY\n");
				move_right(wm, player);
				sleep(2);
				Point player = find_player(mandrage_color_pattern, color_matrix, 2, 2);
				sleep(2);
				printf("Player has moved in (%d, %d)\n", player.x, player.y);
				click(wm, 1200, 1040);
				sleep(15);
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
			}
		}
		Point player = find_player(mandrage_color_pattern, color_matrix, 2, 2);
		sleep(2);
		printf("Player has moved in (%d, %d)\n", player.x, player.y);
		click(wm, 1200, 1040);
		sleep(15);
	}
	printf("ENEMY IN RANGE: %dx %dy close\n", player.x - enemy.x, player.y - enemy.y);
	return 1;
}

void	boost(WinManager *wm, Point player)
{
	click(wm, 1440, 975);
	click(wm, player.x, player.y);
	sleep(1);
	click(wm, 1590, 975);
	click(wm, player.x, player.y);
	sleep(1);
}

// this function compare the blue color sequence with the color sequence in zone

void	attack(WinManager *wm, Point enemy)
{
	click(wm, 1390, 975);
	sleep(.5);
	click(wm, enemy.x, enemy.y);
	sleep(2);
}

void	end_tour(WinManager *wm)
{
	click(wm, 1200, 1040);
	sleep(2);
}

void	close_fight_window(WinManager *wm)
{
	click(wm, 1326, 723);
	sleep(1);
}
