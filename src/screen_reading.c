#include "screen_reading.h"
#include "window_manager.h"
#include <stdlib.h>

Rgb orange_button = {.r = 230, .g = 87, .b = 0};

Rectangle create_rectangle(int x, int y, unsigned int width, unsigned int height)
{
	Rectangle rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.width = width;
	rectangle.height = height;
	return rectangle;
}


XImage	*get_zone_to_check(WinManager *wm, Rectangle rectangle)
{
	XImage *zone_to_check;
	zone_to_check = XGetImage(wm->display,
	wm->root,
	rectangle.x,
	rectangle.y,
	rectangle.width,
	rectangle.height,
	AllPlanes,
	ZPixmap);
	return zone_to_check;
}

int	get_bit_shift(unsigned long color_mask)
{
	int shift = 0;
	while ((color_mask & 1) == 0)
	{
		color_mask >>= 1;
		shift++;
	}
	return shift;
}

Rgb*	convert_pixel_to_rgb(XImage *zone_to_check, unsigned long pixel)
{
	Rgb *rgb;
	int red_shift, green_shift, blue_shift = 0;
	red_shift = get_bit_shift(zone_to_check->red_mask);
	green_shift = get_bit_shift(zone_to_check->green_mask);
	blue_shift = get_bit_shift(zone_to_check->blue_mask);
	rgb->r = (pixel & zone_to_check->red_mask) >> red_shift;
	rgb->g = (pixel & zone_to_check->green_mask) >> green_shift;
	rgb->b = (pixel & zone_to_check->blue_mask) >> blue_shift;
	return rgb;
}

void	get_pixel_color_code(WinManager *wm, Rectangle rectangle, XImage *zone_to_check)
{
	if (!zone_to_check)
	{
		printf("could not define rectangle zone\n");
		return ;
	}
	printf("IMG WIDTH:%d \nIMG HEIGHT:%d\nIMG DEPTH:%d\n", 
	zone_to_check->width, zone_to_check->height, zone_to_check->depth);
	for (int i = 0; i < zone_to_check->height ; i++)
	{
		for (int j = 0; j < zone_to_check->width ; j++)
		{
			unsigned long pixel = XGetPixel(zone_to_check, j, i);
			Rgb* color = convert_pixel_to_rgb(zone_to_check, pixel);
			printf("(%d, %d): R%d G%d B%d\n",
			(j+rectangle.x), (i+rectangle.y), color->r, color->g, color->b);
		}
	}
}

int	check_frame(Rgb* color, Rgb orange_button, XImage *zone_to_check)
{
	// pour la frame 1
	// on a un counter de orange
	int orange_counter = 0;
	if (orange_counter > 10)
	{
		printf("frame 1\n");
		return 1;
	}
}

// releve la couleur recherche sur la zone
// on peut faire un carre de 10*10 
// si la couleur correspond a la couleur du ble 
// click sur les coordonnes (x y)
// sinon en deduire la current frame

