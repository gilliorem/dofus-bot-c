#ifndef SCREEN_READING_H
#define SCREEN_READING_H

#include <stdio.h>
#include "window_manager.h"
 

typedef struct
{
	int x;
	int y;
	unsigned int width;
	unsigned int height;
} Rectangle;

typedef struct
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
}Rgb;

extern Rgb orange_button;
Rectangle	create_rectangle(int x, int y, unsigned int width, unsigned int height);
XImage	*get_zone_to_check(WinManager *wm, Rectangle rectangle);
int	get_bit_shift(unsigned long color_mask);
Rgb*	convert_pixel_to_rgb(XImage *zone_to_check, unsigned long pixel);
void	get_pixel_color_code(WinManager *wm, Rectangle rectangle, XImage *zone_to_check);

#endif
