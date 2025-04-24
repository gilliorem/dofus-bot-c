#include "mouse_manager.h"
#include <math.h>
#include <stdlib.h>
#include "types.h"

//ajouter un check pour voir si l'arme est deja equipee
// weapon etant dans ce cas l'arme de cac (ici, marteau bouftou)
int	check_weapon(WinManager *wm)
{
	Rgb ref = {.r = 255, .g = 255, .b = 255};
	int tolerance = 5;
	Rectangle scythe_zone = create_rectangle(1274, 968, 1, 1);
	XImage *scythe_image = get_zone_to_check(wm, scythe_zone);
	unsigned long pixel = XGetPixel(scythe_image, 0, 0);
	Rgb scythe_color = convert_pixel_to_rgb(scythe_image, pixel);
	Rectangle weapon_zone = create_rectangle(1321, 968, 1, 1);
	XImage *weapon_image = get_zone_to_check(wm, weapon_zone);
	unsigned long w_pixel = XGetPixel(weapon_image, 0, 0);
	Rgb weapon_color = convert_pixel_to_rgb(weapon_image, w_pixel);
	if (abs(ref.r - weapon_color.r) < tolerance)
	{
		printf("Weapon equip\n");
		return 1;
	}
	else if (abs(ref.r - scythe_color.r) < tolerance)
	{
		printf("Faux is equip\n");
		return 2;
	}
	printf("checking-weapon-state is incorrect \n");
	return 0;
}

void	equip_weapon(WinManager *wm)
{
	if (check_weapon(wm) == 2)
	{
		printf("switching to weapon\n");
		double_click(wm, 1320, 968);
	}
}

// in order to check if still in combat mode can check the pixel in 1080, 1025 (white flag)
// check foireux car l'icone bouge : faire un check sur un autre element static, ou implementer un check dynamique 
// qui cherche l'icon et qui check son etat (couleur);

int	check_tactical_mode(WinManager *wm)
{
	Rgb ref = {.r = 0, .g = 153, .b = 0};
	int tolerance = 5;
	Rectangle tactical_zone = create_rectangle(1533, 754, 1, 1);
	XImage *tactical_image = get_zone_to_check(wm, tactical_zone);
	unsigned long pixel = XGetPixel(tactical_image, 0, 0);
	Rgb tactical_color = convert_pixel_to_rgb(tactical_image, pixel);
	printf("%d %d %d\n", tactical_color.r, tactical_color.g, tactical_color.b);
	if (abs(ref.r - tactical_color.r) < tolerance)
	{
		printf("Tactical mode ON.\n");
		return 1;
	}
	printf("Tactical mode OFF\n");
	return 0;
}

void	tactical_mode(WinManager *wm)
{
	if (check_tactical_mode(wm) == 1)
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
	move_mouse(wm, player_pos.x + 150, player_pos.y + 75);
	sleep(.5);
	fake_click(wm, 1, True);
	printf("move right\n");
}

void	move_left(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x - 150, player_pos.y + 75);
	sleep(.5);
	fake_click(wm, 1, True);
	printf("moved left\n");
}

void	move_up(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x + 50, player_pos.y - 75);
	sleep(.5);
	fake_click(wm, 1, True);
	printf("moved up \n");
}

void	move_down(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x - 50, player_pos.y + 75);
	sleep(.5);
	fake_click(wm, 1, True);
	printf("moved down\n");
}

void	move_down_right(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x + 50, player_pos.y + 75);
	sleep(.4);
	fake_click(wm, 1, True);
	printf("moved down right\n");
}

void	move_down_left(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x - 125, player_pos.y + 75);
	sleep(.5);
	fake_click(wm, 1, True);
	printf("moved down left\n");
}

void	move_up_right(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x + 100, player_pos.y - 75);
	sleep(.5);
	fake_click(wm, 1, True);
	printf("moved up right\n");
}

void	move_up_left(WinManager *wm, Point player_pos)
{
	move_mouse(wm, player_pos.x - 100, player_pos.y - 75);
	sleep(.5);
	fake_click(wm, 1, True);
	printf("moved up left\n");
}

// find the closest path between player and enemy+
int	move_towards_enemy(WinManager *wm, Rgb color_matrix[1080][1920])
{
	int counter = 0;
	Point player = find_player(mandrage_color_pattern, color_matrix, 2, 2);
	Point enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 10, 2);
	while (abs(player.x - enemy.x) > 50 || abs(player.y - enemy.y) > 50 && counter <= 10)
	{
		player = find_player(mandrage_color_pattern, color_matrix, 2, 2);
		enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 10, 2);
		if (abs(player.x - enemy.x) > 50 || abs(player.x - enemy.x) > abs(player.y - enemy.y))
		{
			if (player.x > enemy.x)
			{
				printf("PlayerX < EnemyX : MOVE LEFT\n");
				move_left(wm, player);
				sleep(2);
				Point player_ = find_player(mandrage_color_pattern, color_matrix, 2, 2);
				if (player.x == player_.x )
					move_up_left(wm, player);
				sleep(2);
				printf("Player has moved in (%d, %d)\n", player.x, player.y);
				click(wm, 1200, 1040);
				sleep(15);
			}
			else if (player.x < enemy.x)
			{
				printf("PLAYER X > ENEMY X MOVE RIGHT \n");
				move_right(wm, player);
				sleep(2);
				Point player_ = find_player(mandrage_color_pattern, color_matrix, 2, 2);
				if (player.x == player_.x )
				{
					move_up_right(wm, player);
					sleep(.5);
					XSync(wm->display, False);
				}
				sleep(2);
				printf("Player has moved in (%d, %d)\n", player.x, player.y);
				click(wm, 1200, 1040);
				sleep(15);
			}
		}
		else if (abs(player.y - enemy.y) > 50)
		{
			if (player.y < enemy.y)
			{
				printf("PLAYER IS 'ABOVE' ENEMY: PLAYER MOVE DOWN \n");
				move_down(wm, player);
				sleep(2);
				Point player_ = find_player(mandrage_color_pattern, color_matrix, 2, 2);
				if (player.y == player_.y)
				{
					move_down_right(wm, player);
					player_ = find_player(mandrage_color_pattern, color_matrix, 2, 2);
					if (player.y == player_.y)
						move_down_left(wm, player);
				}
			}
			else if (player.y > enemy.y)
			{
				printf("PLAYER IS 'BELOW' ENEMY: PLAYER MOVE UP \n");
				move_up(wm, player);
				sleep(2);
				Point player_ = find_player(mandrage_color_pattern, color_matrix, 2, 2);
				if (player.y == player_.y )
					move_up_right(wm, player);
			}
		}
		Point player = find_player(mandrage_color_pattern, color_matrix, 2, 2);
		sleep(2);
		printf("Player has moved in (%d, %d)\n", player.x, player.y);
		click(wm, 1200, 1040);
		sleep(15);
		counter++;
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
