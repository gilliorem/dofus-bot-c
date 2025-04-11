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
	Rgb color_matrix[1920][1080];


	Rectangle zone = create_rectangle(0, 0, 1920, 1080);
	XImage *image_zone = get_zone_to_check(wm, zone);
	Point pixel_match[216];
	build_color_matrix(color_matrix, image_zone, zone);
	Rectangle pods_zone = create_rectangle(1226, 482, 10, 4);
	XImage *pods_image = get_zone_to_check(wm, pods_zone);
	
	while (1)
	{
		int cereals = compare_color_pattern(wm, barley_color_pattern, color_matrix, 3,  pixel_match);
		if (cereals < 1)
			break;
		check_orange_color_pods(wm, pods_image);
	}
	
	
	/*
	while(1)
	{
		get_mouse_coordinates(wm, p);
		Rectangle barley_zone = create_rectangle(1461, 426, 3, 2);
		get_color_sequence(wm, barley_zone);
		sleep(2);
		XSync(wm->display, False);
	}
	*/
	
	return (0);
}
