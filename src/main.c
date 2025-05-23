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
#include "gui.h"

WinManager *wm = NULL;
// why init pointer wm to NULL ?
// ooow so we can use this variable and actually set it to smthg
GtkApplication *app = NULL;
WinManager* get_wm()
{
	return (wm);
}

GtkApplication *get_gtk_app()
{
	return (app);
}

int	main(void)
{
	wm = init_bot();
	//app = get_gtk_app();

	//log_in(wm);
	launch_gui(app, wm);
/*
	static Rgb color_matrix[1080][1920];
	build_color_matrix(wm, color_matrix);
	Point grey_tile[1900];
	while (1)
	{
		if (reap_flax(wm, color_matrix))
		{
			placement(wm, color_matrix);
			find_player_range_tiles(wm, color_matrix);
			if (end_of_fight(wm)==1)
				break;
		}

	}
*/
	return (0);
}
