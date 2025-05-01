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
	static Rgb color_matrix[1080][1920];
	build_color_matrix(wm, color_matrix);
	Point grey_tile[1900];

	while (1)
	{
		if (reap_hop(wm, color_matrix))
		{
			placement(wm, color_matrix);
			find_player_range_tiles(wm, color_matrix);
			if (end_of_fight(wm)==1)
				break;
		}

	}
	return (0);
}

