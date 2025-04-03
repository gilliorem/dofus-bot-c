#include <stdio.h>
#include <stdlib.h>
#include "window_manager.h"
#include "event_handler.h"
#include "screen_reading.h"

int	main(void)
{
	WinManager *wm = setXConnection();
	if (!wm) return 1;
	Point p;
	Rectangle zone_to_check = create_rectangle(700, 450, 400, 200);
	get_pixel_color_code(wm, zone_to_check);	
	while (1)
	{
		get_mouse_coordinates(wm, &p);
		XSync(wm->display, False);
	}

	return (0);
}
