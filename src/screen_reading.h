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
	unsigned char r;
	unsigned char g;
	unsigned char b;
}Rgb;

extern Rgb orange_button;
extern Rgb log_in_button;
Rectangle	create_rectangle(int x, int y, unsigned int width, unsigned int height);
XImage	*get_zone_to_check(WinManager *wm, Rectangle rectangle);
int	get_bit_shift(unsigned long color_mask);
Rgb	convert_pixel_to_rgb(XImage *zone_to_check, unsigned long pixel);
Rgb*	get_color_in_frame(WinManager *wm, XImage *zone_to_check);
int	check_color(XImage *zone_to_check);
int	check_log_in(XImage *zone_to_check);
int	check_orange_color(XImage *zone_to_check);
XImage	**get_nzone(WinManager *wm, int n);
int	compare_colors(XImage *zone_to_check_a, XImage *zone_to_check_b);
int	check_frame(WinManager *wm);
void	start(WinManager *wm);

#endif
