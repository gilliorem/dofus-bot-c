#include <stdio.h>
#include <stdlib.h>
#include "window_manager.h"
#include "event_handler.h"
#include "screen_reading.h"
#include "types.h"

int	main(void)
{
	WinManager *wm = setXConnection();
	if (!wm) return 1;
	Point p;

	//log_in(wm);
	//sleep(5);
	Rgb color_matrix[1080][1920];

	Rectangle screen_zone = create_rectangle(0, 0, 1920, 1080);
	XImage *screen_image = get_zone_to_check(wm, screen_zone);
	build_color_matrix(color_matrix, screen_image, screen_zone);

/*	Point player = find_player(mandrage_color_pattern, color_matrix, 2, 1);
	Point enemy = find_enemy(color_matrix, scarecrow_hat_dark_brown, 9, 2);
	Point red_square[256];
	int red_square_counter = get_red_square_pos(color_matrix, 80, 2, player, enemy, red_square);
	Point placement = find_closest_placement_to_enemy(red_square, red_square_counter, enemy);
	place_player(wm, placement);
*/
	move_towards_enemy(wm, color_matrix);
	

/*
	while (1)
	{
		int cereals = compare_color_pattern(wm, hop_color_pattern, color_matrix, 5, 10);
		if (cereals < 1)
			return 0;
		check_orange_color_pods(wm, pods_image);
	}
*/
	sleep(2);
	XSync(wm->display, False);
	return (0);
}
