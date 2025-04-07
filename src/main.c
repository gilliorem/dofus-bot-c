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

/*	Rectangle rectangle = create_rectangle(1000, 650, 10, 10);
	XImage *zone_to_check = get_zone_to_check(wm, rectangle);
	get_color_in_frame(zone_to_check);	
	check_orange_color(zone_to_check);	
*/	
	int n_zone = 2;
	XImage **zones_to_check = get_nzone(wm, n_zone);
	check_frame(zones_to_check, n_zone);
		
	

//	get_mouse_coordinates(wm, &p);
	XSync(wm->display, False);

	return (0);
}
