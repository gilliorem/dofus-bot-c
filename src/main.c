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

	Rectangle rectangle = create_rectangle(1000, 650, 10, 10);
	// modify create_rectangle into create zone_to_check so I can pass only the zone in
	// get_color_in_frame
	XImage *zone_to_check = get_zone_to_check(wm, rectangle);
	get_color_in_frame(rectangle, zone_to_check);	
	check_color(zone_to_check);	

	get_mouse_coordinates(wm, &p);
	XSync(wm->display, False);

	return (0);
}
