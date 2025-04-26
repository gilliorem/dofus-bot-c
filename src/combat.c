#include "mouse_manager.h"
#include <math.h>
#include <stdlib.h>
#include "types.h"
#include "combat.h"
#include "screen_reading.h"

//ajouter un check pour voir si l'arme est deja equipee
// weapon etant dans ce cas l'arme de cac (ici, marteau bouftou)
enum Weapon	check_weapon(WinManager *wm)
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
		printf("Hammer equip\n");
		return WEAPON_HAMMER;
	}
	else if (abs(ref.r - scythe_color.r) < tolerance)
	{
		printf("Faux is equip\n");
		return WEAPON_SCYTHE;
	}
	printf("checking-weapon-state is incorrect \n");
	return 0;
}

void	equip_weapon(WinManager *wm)
{
	if (check_weapon(wm) != WEAPON_HAMMER)
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

void placement(WinManager *wm, Rgb color_matrix[1080][1920])
{
	build_color_matrix(wm, color_matrix);
	Point red_square[50];
	Point player_pos = find_player(mandrage_color_pattern, color_matrix, 3, 5);
	Point enemy_pos = find_enemy (color_matrix, scarecrow_hat_dark_brown, 9, 2);
	int red_squares = get_red_square_pos(color_matrix, 88, 3, player_pos, enemy_pos, red_square);
	if (red_squares < 1)
		return;
	player_pos = find_closest_placement_to_enemy(red_square, red_squares, enemy_pos);
	place_player(wm, player_pos);
	click_ready_button(wm);
	sleep(2);
}

void	move(WinManager *wm, int x, int y)
{
	move_mouse(wm, x, y); 
	sleep(.5);
	fake_click(wm, 1, True);
	sleep(1);
	XSync(wm->display, False);
}

int	move_towards_enemy_x(WinManager *wm, Rgb color_matrix[1080][1920])
{
	int counter = 0;
	Point player = find_player(red_color_pattern, color_matrix, 32, 2);
	Point enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 10, 2);
	while (abs(player.x - enemy.x) > 80 || counter > 4)
	{
		build_color_matrix(wm, color_matrix);
		player = find_player(red_color_pattern, color_matrix, 32, 2);
		enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 10, 2);
		if ((player.x - enemy.x) < 105 && (player.x - enemy.x) > 49)
		{
			move(wm, player.x - 45, player.y + 25);
			counter++;
			break;
		}
		else if (player.x > enemy.x)
		{
			printf("PlayerX > EnemyX : Move de -150x, +100y\n");
			move(wm, player.x - 135, player.y + 80);
			sleep(2);
			build_color_matrix(wm, color_matrix);
			Point new_player = find_player(red_color_pattern, color_matrix, 32, 2);
			if (new_player.x == player.x)
				move(wm, player.x - 45, player.y + 25);
			click(wm, 1200, 1040);
			printf("Player has moved in (%d, %d)\n", new_player.x, new_player.y);
			sleep(15);
			counter++;
		}
		else if ((enemy.x - player.x) < 150 && (enemy.x - player.x) > 49)
		{
			move(wm, player.x + 45, player.y - 25);
			counter++;
			break;
		}
		else if (player.x < enemy.x)
		{
			printf("PLAYER X < ENEMY X: MOVE RIGHT \n");
			move(wm, player.x + 135, player.y - 80);
			sleep(2);
			build_color_matrix(wm, color_matrix);
			Point new_player = find_player(red_color_pattern, color_matrix, 32, 2);
			if (new_player.x == player.x)
				move(wm, player.x + 45, player.y - 25);	
			printf("Player has moved in (%d, %d)\n", new_player.x, new_player.y);
			click(wm, 1200, 1040);
			sleep(15);
			counter++;
		}
	}
	printf("pX and eX 50 pixel close\n");
	return 0;
}

int	move_towards_enemy_y(WinManager *wm, Rgb color_matrix[1080][1920])
{
	int counter = 0;
	Point player = find_player(red_color_pattern, color_matrix, 32, 2);
	Point enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 10, 2);
	while (abs(player.y - enemy.y) > 80 || counter > 4)
	{
		build_color_matrix(wm, color_matrix);
		player = find_player(red_color_pattern, color_matrix, 32, 2);
		enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 10, 2);
		if ((player.y - enemy.y) < 50 && (player.y - enemy.y) > 40)
		{
			move(wm, player.x - 66, player.y - 30);
			break;
		}
		else if (player.y > enemy.y)
		{
			printf("PlayerY > EnemyY : Move de -150x, +100y\n");
			move(wm, player.x - 145, player.y - 75);
			counter++;
			sleep(2);
			player = find_player(red_color_pattern, color_matrix, 32, 2);
			printf("Player has moved in (%d, %d)\n", player.y, player.y);
			click(wm, 1200, 1040);
			sleep(15);
		}
		else if ((player.y - enemy.y) > 105 && (enemy.y - player.y) > 49)
		{
			move(wm, player.x - 45, player.y - 25);
			break;
		}
		else if (player.y < enemy.y)
		{
			printf("PLAYER Y < ENEMY Y MOVE DOWN \n");
			move(wm, player.x + 145, player.y + 60);
			counter++;
			sleep(2);
			player = find_player(red_color_pattern, color_matrix, 32, 2);
			printf("Player has moved in (%d, %d)\n", player.x, player.y);
			click(wm, 1200, 1040);
			sleep(15);
		}
	}
	printf("pY and eY 50 pixel close\n");
	return 0;
}

void	boost(WinManager *wm, Rgb color_matrix[1080][1920])
{
	build_color_matrix(wm, color_matrix);
	Point player = find_player(mandrage_color_pattern, color_matrix, 2, 3);
	int x = 1285;
	for(int i = 0; i < 3; i++)
	{
		click(wm, x, 975);
		click(wm, player.x, player.y);
		x+= 50;
	}
	end_tour(wm);
}

void	attack(WinManager *wm, Rgb color_matrix[1080][1920])
{
	while (check_enemy_life(wm, color_matrix) != 0 && end_of_fight(wm) != 1 && is_my_turn(wm) == 1)
	{
		build_color_matrix(wm, color_matrix);
		Point enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 9, 4);
		for (int i = 0; i < 2; i++)
		{
			if (check_enemy_life(wm, color_matrix) != 0)
			{
				click(wm, 1440, 975);
				click(wm, enemy.x, enemy.y);
				sleep(1);
			}
			else if (is_my_turn(wm) != 1)
				sleep(4);
		}
		end_tour(wm);
	}
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
