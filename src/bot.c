/*
#include "log.h"
#include "window_manager.h"
#include "mouse_manager.h"
#include "screen_reading.h"
#include "farmer.h"
#include "combat.h"

void	run()
{
	WinManager *wm = init_bot();
	if (log_in(wm) == 0)
		return;
	Rgb color_matrix[1080][1920];
	build_color_matrix(wm, color_matrix);
	while (1)	
	{
	//	int farming = 1;
		
		int farming = reap_wheat(wm, color_matrix);
		farming = reap_barley(wm, color_matrix);
		farming = reap_oat(wm, color_matrix);
		farming = reap_hop(wm, color_matrix);
		switch (farming)
		{
			case 1:
				equip_weapon(wm);
				tactical_mode(wm);
				Point player_pos = find_player(mandrage_color_pattern, color_matrix, 3, 3);
				Point enemy_pos = find_enemy(color_matrix, scarecrow_hat_dark_brown, 5, 3);
				Point red_square[50];
				int red_squares = get_red_square_pos(color_matrix, 88, 3, player_pos, enemy_pos, red_square);
				player_pos = find_closest_placement_to_enemy(red_square, red_squares, enemy_pos);
				place_player(wm, player_pos);
				click_ready_button(wm);
				sleep(15);
				while (1)
					if (move_towards_enemy_x(wm, color_matrix) == 1)
						break;
				player_pos = find_player(mandrage_color_pattern, color_matrix, 3, 3);
				enemy_pos = find_enemy(color_matrix, scarecrow_hat_dark_brown, 5, 3);
				//boost(wm, player_pos);
				for (int i = 0; i < 2; i ++)
					//attack(wm, enemy_pos);
				end_tour(wm);
				//if (check_enemy_life(wm) == 1)
				//	farming = 0;
				while (is_my_turn(wm) != 1)
					sleep(2);
				enemy_pos = find_enemy(color_matrix, scarecrow_hat_dark_brown, 5, 3);
				if (move_towards_enemy_y(wm, color_matrix) == 1)
				{
					for (int i = 0; i < 2; i++);
						//attack(wm, enemy_pos);
				}
				//if (check_enemy_life(wm) == 1)
				//	farming = 0;
			case 3:
				close_fight_window(wm);
				equip_scythe(wm);
				break;
		}	

	}
	sleep(2);
	XSync(wm->display, False);
}	

*/
