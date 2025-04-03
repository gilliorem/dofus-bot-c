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

Rectangle	create_rectangle(int x, int y, unsigned int width, unsigned int height);
void	get_pixel_color_code(WinManager *wm, Rectangle rectangle);
short*	convert_pixel_to_rgb(long pixel);

#endif
