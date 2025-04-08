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

	//log_in(wm);
	Rectangle r_zone = create_rectangle(400, 150, 200, 100);
	XImage *zone = get_zone_to_check(wm, r_zone);
	while (1)
	{
		is_wheat(wm, wheat, zone, r_zone);
		sleep(5);
	}
	
	
//	check_frame(wm);
		
//	while (1)
	//	get_mouse_coordinates(wm, &p);
	sleep(1);
	XSync(wm->display, False);

	return (0);
}
