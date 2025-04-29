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
	WinManager *wm = init_bot();
	Rgb color_matrix[1080][1920];
	build_color_matrix(wm, color_matrix);
	Point player = find_player(color_matrix, red_color_pattern, 34, 5);
	Point enemy = find_enemy(color_matrix, blue_color_pattern, 34, 5);
	Point grey_tile[300];
	int light_tiles = get_light_grey_tiles(color_matrix, 92, 5, grey_tile);
	int dark_tiles = get_dark_grey_tiles(color_matrix, 92, 5, grey_tile);
	int grey_tiles = light_tiles + dark_tiles;
	while (1)
	{
		int in_range_tiles =  move_in_range(wm, color_matrix, grey_tile, grey_tiles);
		sleep(4);
		XSync(wm->display, False);

	}
	return (0);
}


