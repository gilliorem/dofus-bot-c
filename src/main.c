#include <stdio.h>
#include <stdlib.h>
#include "window_manager.h"
#include "screen_reading.h"
#include "log.h"
#include "mouse_manager.h"
#include "farmer.h"
#include "combat.h"
#include "types.h"
#include "bot.h"

int	main(void)
{

	//run();
	WinManager *wm = init_bot();
	Rgb color_matrix[1080][1920];
	build_color_matrix(wm, color_matrix);
	// gerer les cas ou on est sur le log in screen 
	// differencier in_game_screen de in combat
/*
	if (check_in_game(wm) == 1) 
		if (ready_button_visible(wm) == 1)
			equip_weapon(wm);
	Point enemy_pos = find_enemy(color_matrix, scarecrow_hat_dark_brown, 9, 2);
	Point red_square[50];
	int red_squares = get_red_square_pos(color_matrix, 88, 3, player_pos, enemy_pos, red_square);
	player_pos = find_closest_placement_to_enemy(red_square, red_squares, enemy_pos);
	place_player(wm, player_pos);
*/
	Point player_pos = find_player(mandrage_color_pattern, color_matrix, 2, 3);
	
	move_up(wm, player_pos);
	sleep(3);
	move_up(wm, player_pos);
	//move_towards_enemy(wm, color_matrix);
	sleep(2);
	XSync(wm->display, False);
	return (0);
}
