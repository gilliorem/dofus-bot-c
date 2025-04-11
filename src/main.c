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
	Point pixel_match[216];
	Rectangle pods_zone = create_rectangle(1226, 482, 10, 4);
	XImage *pods_image = get_zone_to_check(wm, pods_zone);
	
	while (1)
	{
		XImage *image_zone = get_zone_to_check(wm, zone);
		build_color_matrix(color_matrix, image_zone, zone);
		int cereals = compare_color_pattern(wm, hop_color_pattern, color_matrix, 2,  pixel_match, 1);
		if (cereals < 1)
			return 0;
		check_orange_color_pods(wm, pods_image);
	}

	while(1)
	{
		get_mouse_coordinates(wm, p);
		Rectangle ready_button_zone = create_rectangle(1524, 806, 10, 1);
		//get_color_sequence(wm, ready_button_zone);
		sleep(2);
		XSync(wm->display, False);
	}

	return (0);
}
