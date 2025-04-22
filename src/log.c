#include "log.h"
#include "mouse_manager.h"
#include "screen_reading.h"

int	start(WinManager *wm)
{
	move_mouse(wm, 544, 530);
	int i = 0;
	while (i < 3)
	{
		double_click(wm);
		sleep(4);
		i++;
	}

	return 0;
}

int	log_in(WinManager *wm)
{
	Rectangle log_in_zone = create_rectangle(692, 490, 25, 20);
	XImage *log_in_image = get_zone_to_check(wm, log_in_zone);
	if (ok_button_visible(wm))	
		click(wm, 1000, 650);
	else if (check_log_in(log_in_image) == 1)
		click(wm, 544, 53);
	ok_button_visible(wm);	
	sleep(1);
	start(wm);
	return 0;
}


