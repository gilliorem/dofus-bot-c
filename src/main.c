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
	Point grey_tile[300];
	int grey_tiles = get_grey_tiles(color_matrix, 93, 4, grey_tile);
	Point in_range_tile[grey_tiles];
	Point player = find_player(red_color_pattern, color_matrix, 34, 3);
	int tiles_in_range = get_in_range_tile(wm, grey_tile, grey_tiles, player, in_range_tile);
	Point enemy_pos = find_enemy(color_matrix, blue_color, 34, 3);
	move_in_tile(wm, tiles_in_range, in_range_tile, player, enemy_pos);
/*
	reap_hop(wm, color_matrix);
	equip_weapon(wm);
	placement(wm, color_matrix);
	boost(wm, color_matrix);
	attack(wm, color_matrix);
	close_fight_window(wm);

	for (int i = 0; i < 5; i++)
	{
		build_color_matrix(wm, color_matrix);
		Point player_pos = find_player(mandrage_color_pattern, color_matrix, 2, 3);
		boost(wm, player_pos);
		attack(wm, enemy_pos);
		attack(wm, enemy_pos);
		end_tour(wm);
		sleep(10);
	}
	close_fight_window(wm);
*/	
	sleep(2);
	XSync(wm->display, False);
	return (0);
}
