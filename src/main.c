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
	check_weapon(wm);
/*
	tactical_mode(wm);
	Point player_pos = find_player(mandrage_color_pattern, color_matrix, 3, 3);
	Point enemy_pos = find_enemy(color_matrix, scarecrow_hat_dark_brown, 5, 3);
	Point red_square[50];
	int red_squares = get_red_square_pos(color_matrix, 88, 3, player_pos, enemy_pos, red_square);
	player_pos = find_closest_placement_to_enemy(red_square, red_squares, enemy_pos);
	place_player(wm, player_pos);

	Point player = find_player(mandrage_color_pattern, color_matrix, 2, 1);
	Point enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 9, 2);
	Point red_square[256];
	int red_square_counter = get_red_square_pos(color_matrix, 80, 2, player, enemy, red_square);
	Point placement = find_closest_placement_to_enemy(red_square, red_square_counter, enemy);
	place_player(wm, placement);
*/
//	move_towards_enemy(wm, color_matrix);
	
/*
	Point matches[216];
	int size = find_matching_pattern(oat_color_pattern, color_matrix, 3, 8, matches);
	print_matching_pattern_position(size, matches);
	sleep(2);
	XSync(wm->display, False);
*/
	return (0);
}
