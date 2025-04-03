#include "screen_reading.h"
#include "window_manager.h"

Rectangle create_rectangle(int x, int y, unsigned int width, unsigned int height)
{
	Rectangle rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.width = width;
	rectangle.height = height;
	return rectangle;
}

void	get_pixel_color_code(WinManager *wm, Rectangle rectangle)
{
	printf("rect.x=%d rect.y=%d rect.w=%u rect.h=%u\n",
	rectangle.x, rectangle.y, rectangle.width, rectangle.height);

	XImage *zone_to_check = XGetImage(wm->display,
	wm->root,
	rectangle.x,
	rectangle.y,
	rectangle.width,
	rectangle.height,
	AllPlanes,
	ZPixmap);

	if (!zone_to_check)
	{
		printf("could not define rectangle zone\n");
		return ;
	}

	printf("IMG WIDTH:%d \nIMG HEIGHT:%d\nIMG DEPTH:%d\n", 
	zone_to_check->width, zone_to_check->height, zone_to_check->depth);
	for (int i = 0; i < zone_to_check->height ; i++)
	{
		printf("checking Y %d\n", i + rectangle.y);
		for (int j = 0; j < zone_to_check->width ; j++)
		{
			long pixel = XGetPixel(zone_to_check, j, i);
			printf("checking X %d\n", j + rectangle.x);
			printf("pixel code : %ld\n", pixel);

		}
	}
	XDestroyImage(zone_to_check);
}

short*	convert_pixel_to_rgb(long pixel)
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}
