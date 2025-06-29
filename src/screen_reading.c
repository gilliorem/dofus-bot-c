#include "types.h"
#include <stdlib.h>
#include <unistd.h>
#include "screen_reading.h"
#include "mouse_manager.h"
#include "window_manager.h"

#define FIGHT_W     1360
#define FIGHT_H      790
#define PO_W       388
#define PO_H       161
#define HALF_PO_W (PO_W / 2)   /* 194 */
#define HALF_PO_H (PO_H / 2)   /* 80  */

Rgb orange_button = {.r = 255, .g = 102, .b = 0};
Rgb ok_orange_button = {.r = 255, .g = 97, .b = 0};
Rgb grey = {.r = 213, .g = 207, .b = 170};
Rgb log_in_button = {.r = 255, .g = 255, .b = 255};
Rgb wheat = {.r = 56, .g = 62, .b = 15};
Rgb ready_button = {.r = 252, .g = 109, .b = 36, "Orange(ready button)"};

static Rgb screen_matrix[1080][1920];
static Rgb screen_matrix_v[1920][1080];

void update_screen_matrix(WinManager *wm)
{
	build_color_matrix(wm, screen_matrix);
}

void update_screen_matrix_v(WinManager *wm)
{
	build_color_matrix_vertical(wm, screen_matrix_v);
}

Rgb (*get_screen_matrix(void))[1920]
{
	return screen_matrix;
}

Rgb (*get_screen_matrix_v(void))[1080]
{
	return screen_matrix_v;
}


Rgb red_arrow_icon = {240, 39, 45, "Red(arrow icon)"};

Rgb_pattern*	create_rgb_pattern(Rgb color, int width)
{
	Rgb_pattern *color_pattern = malloc(sizeof(Rgb_pattern));
	color_pattern->width = width;
	color_pattern->color = malloc(width * sizeof(Rgb));
	for (int i = 0; i < width; i++)
	{
		color_pattern->color[i] = color;
		printf("R:%d G:%d B:%d\n", color_pattern->color[i].r, color_pattern->color[i].g, color_pattern->color[i].b);
	}
	return color_pattern;
}



Rgb white_pattern[6] = {
	{.r = 255, .g = 255, .b = 255},
	{.r = 255, .g = 255, .b = 255},
	{.r = 255, .g = 255, .b = 255},
	{.r = 255, .g = 255, .b = 255},
	{.r = 255, .g = 255, .b = 255},
	{.r = 255, .g = 255, .b = 255}
};

Rgb mandrage_color_pattern[3] = {
	{.r = 138, .g = 0, .b = 7},
	{.r = 138, .g = 0, .b = 7},
	{.r = 74, .g = 4, .b = 35}
};

Rgb context_menu_light_gray[3] = {
	{.r = 173, .g = 165, .b = 126},
	{.r = 173, .g = 165, .b = 126},
	{.r = 173, .g = 165, .b = 126}
};

Rgb context_menu_dark_gray[3] = {
	{.r = 81, .g = 74, .b = 60},
	{.r = 81, .g = 74, .b = 60},
	{.r = 81, .g = 74, .b = 60}
};

Rgb wheat_color_pattern[4] = {
	{.r = 169, .g = 122, .b = 24},
	{.r = 161, .g = 101, .b = 4},
	{.r = 168, .g = 107, .b = 9},
	{.r = 176, .g = 125, .b = 18}
};

Rgb wheat_color_pattern_vertical[8] = {
	{.r = 174, .g = 105, .b = 21},
	{.r = 174, .g = 105, .b = 21},
	{.r = 174, .g = 105, .b = 21},
	{.r = 174, .g = 101, .b = 20},
	{.r = 171, .g = 98, .b = 20},
	{.r = 166, .g = 97, .b = 19},
	{.r = 166, .g = 97, .b = 19},
	{.r = 166, .g = 97, .b = 19}
};

Rgb barley_color_pattern[3] = {
	{.r = 120, .g = 130, .b = 0},
	{.r = 116, .g = 130, .b = 1},
	{.r = 120, .g = 133, .b = 0}
};

Rgb oat_color_pattern[3] = {
	{.r = 195, .g = 155, .b = 3},
	{.r = 188, .g = 120, .b = 0},
	{.r = 174, .g = 120, .b = 0},
};

Rgb hop_color_pattern[3] = {
	{.r = 0, .g = 90, .b = 71},
	{.r = 3, .g = 90, .b = 71},
	{.r = 20, .g = 95, .b = 78},
};

Rgb hop_color_pattern_v[6] = {
	{.r = 0, .g = 93, .b = 74},
	{.r = 0, .g = 91, .b = 72},
	{.r = 0, .g = 90, .b = 71},
	{.r = 0, .g = 91, .b = 70},
	{.r = 0, .g = 90, .b = 70},
	{.r = 0, .g = 86, .b = 70}
};

Rgb flax_color_pattern[3] = {
	{.r = 222, .g = 215, .b = 131},
	{.r = 227, .g = 219, .b = 156},
	{.r = 227, .g = 220, .b = 161},
};

Rgb flax_color_pattern_v[6] = {
	{.r = 159, .g = 133, .b = 83},
	{.r = 157, .g = 130, .b = 83},
	{.r = 157, .g = 130, .b = 79},
	{.r = 157, .g = 131, .b = 78},
	{.r = 158, .g = 132, .b = 77},
	{.r = 158, .g = 131, .b = 75}
};

Rgb scarecrow_hat_dark_brown = {.r = 125, .g = 81, .b = 33};
Rgb hop_keeper = {.r = 0, .b = 50, .g = 0};
Rgb blue_color = {.r = 0, .b = 255, .g = 0};
Rgb red_color = {.r = 255, .b = 0, .g = 0};

Rgb blue_color_pattern[36] = {
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
 {.r = 0, .b = 255, .g = 0},
};

Rgb red_color_pattern[36] = {
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
 {.r = 255, .b = 0, .g = 0},
};

Rgb light_grey_pattern[89] = {
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
	{.r = 131, .g = 135, .b = 141},
};

Rgb dark_grey_pattern[89] = {
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
	{.r = 121, .g = 125, .b = 131},
};

Rectangle create_rectangle(int x, int y, unsigned int width, unsigned int height) {
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

Rgb	convert_pixel_to_rgb(XImage *zone_to_check, unsigned long pixel)
{
	Rgb rgb;
	int red_shift = get_bit_shift(zone_to_check->red_mask);
	int green_shift = get_bit_shift(zone_to_check->green_mask);
	int blue_shift = get_bit_shift(zone_to_check->blue_mask);

	rgb.r = (pixel & zone_to_check->red_mask) >> red_shift;
	rgb.g = (pixel & zone_to_check->green_mask) >> green_shift;
	rgb.b = (pixel & zone_to_check->blue_mask) >> blue_shift;
	return rgb;
}

int	print_color_in_frame(WinManager *wm, XImage *zone_to_check)
{
	if (!zone_to_check)
	{
		printf("could not define zone\n");
		return -1;
	}
	for (int i = 0; i < zone_to_check->height ; i++)
	{
		for (int j = 0; j < zone_to_check->width ; j++)
		{
			unsigned long pixel = XGetPixel(zone_to_check, j, i);
			Rgb rgb = convert_pixel_to_rgb(zone_to_check, pixel);
			printf("(%d, %d): %d, %d, %d %ld\n",
			(j), (i), rgb.r, rgb.g, rgb.b, pixel);
		}
	}
	return 1;
}

/* TO BE MOVED */
/* TO BE MODIFIED
 * check_color(Rgb log_in_color)
 */
int	check_log_in(XImage *zone_to_check)
{
	int white_counter = 0;
	int tolerance = 10;
	for (int i = 0; i < zone_to_check->height ; i++)
	{
		for (int j = 0; j < zone_to_check->width ; j++)
		{
			unsigned long pixel = XGetPixel(zone_to_check, j, i);
			Rgb rgb = convert_pixel_to_rgb(zone_to_check, pixel);
			if (abs(rgb.r - log_in_button.r) < tolerance
			&& abs(rgb.g - log_in_button.g) < tolerance
			&& abs(rgb.b - log_in_button.b) < tolerance)
				white_counter++;
		}
	}
	if (white_counter > 30)
	{
		printf("LOG IN BUTTON IN ZONE\n");
		return 1;
	}
	printf("No button\n");
	return 0;
}

/* TO BE MOVED */
/* TO BE MODIFIED 
 * check_pattern(Rgb *orange_color_pattern)
 */
int	check_orange_context_menu_color(XImage *zone_to_check, Rgb orange_button, int tolerance)
{
	int orange_pixel_counter = 0;
	for (int j = 0; j < zone_to_check->height; j++)
	{
		for (int i = 0; i < zone_to_check->width; i++)
		{
			unsigned long pixel = XGetPixel(zone_to_check, j, i);
			Rgb rgb = convert_pixel_to_rgb(zone_to_check, pixel);
			if (abs(rgb.r - orange_button.r) > tolerance
			|| abs(rgb.g - orange_button.g) > tolerance
			|| abs(rgb.b - orange_button.b) > tolerance)
			{
				break;
			}
			else
			{
				orange_pixel_counter++;
			}
		}
	}
	printf("Orange pixels spotted : %d\n", orange_pixel_counter);
	return orange_pixel_counter;
}

/* TO BE REMOVE
 * TO BE MODIFIED
 * -> check_color(orange)
 */
int	check_in_game(WinManager *wm)
{
	Rgb in_game_ref = {.r = 131, .g = 82, .b = 1};
	Rgb log_in_screen_ref = {.r = 245, .g = 216, .b = 167};
	int tolerance = 5;
	Rectangle r = create_rectangle(1314, 884, 1, 1);
	XImage *image = get_zone_to_check(wm, r);
	unsigned long pixel = XGetPixel(image, 0, 0);
	Rgb pixel_color = convert_pixel_to_rgb(image, pixel);
	printf("%d %d %d %ld \n", pixel_color.r, pixel_color.g, pixel_color.b, pixel);
	if (abs(in_game_ref.r - pixel_color.r) < tolerance)
	{
		printf("IN GAME\n");
		return 1;
	}
	else if (abs(log_in_screen_ref.r - pixel_color.r) < tolerance)
	{
		printf("IN LOG IN SCREEN\n");
		return 2;
	}
	printf("COULD NOT SEE ANY DOFUS SCREEN\n");
	return 0;
}

/*logic: scan the spot (1520, 790)
 * get the Rgb
 * check the one in zone
 * to check I'm going to go through the x axis 10 times
 * If i get a line of same-color-pixel, I will declare it's a ready button
 * /!\ Watch out for hover: if during the checking the mouse is hovering th ready button: color changes!
 * I can also determine the length the portable way: going x++ until color change: 1offset
 * going x-- until color change: 2offset
 * same for the ys.
 */

/* TO BE MODIFIED */
int	ready_button_visible(WinManager *wm)
{
	static Rgb small_matrix[100][100];
	build_color_matrix_small(wm, small_matrix, 1486, 758);
	Point orange_list[50];
	Rgb ref = ready_button;
	Rgb tol = {10, 10, 30};
	return 0;
}

/* TO BE MODIFIED */
int	ok_button_visible(WinManager *wm)
{
	Rectangle ok_button_zone = create_rectangle(923, 497, 151, 18);
	XImage *ok_button_image = get_zone_to_check(wm, ok_button_zone);
	if (check_orange_context_menu_color(ok_button_image, ok_orange_button, 5) > 30)
	{
		printf("OK BUTTON found\n");
		return 1;
	}
	Rectangle close_button_zone = create_rectangle(1100, 750, 170, 32);
	XImage *close_button_image = get_zone_to_check(wm, close_button_zone);
	if (check_orange_context_menu_color(close_button_image, ok_orange_button, 5) > 30)
	{
		printf("CLOSE BUTTON found\n");
		click(wm, 1178, 768);
		return 1;
	}
	printf("COULD NOT SEE OK BUTTON keep fauching!\n");
	return 0;
}

/* TO BE MODIFIED */
int	full_pods(WinManager *wm)
{
	Rectangle pods_bar_zone = create_rectangle(1224, 469, 16, 18);
	XImage *pods_bar_image = get_zone_to_check(wm, pods_bar_zone);
	if (check_orange_context_menu_color(pods_bar_image, orange_button, 3) > 100)
	{
		printf("FULL PODS\n");
		return 1;
	}
	printf("NOT FULL PODS YET, Keep fauching\n");
	return 0;
}

void	 print_color_sequence(WinManager *wm, Rectangle zone_r)
{
	XImage *image_zone = get_zone_to_check(wm, zone_r);
	print_color_in_frame(wm, image_zone);
	// why sleep ?
	sleep(1);
	XSync(wm->display, False);
}

int	check_color_pattern(WinManager *wm, Rgb **ref, XImage *img, int len)
{
	Rgb color_pattern[img->height][img->width];

	int y = img->height;
	int x = img->width;
	for (int j = 0; j < y; j++)
	{
		printf("Scanning new line...n");
		for (int i = 0; i < x; i++)
		{
			printf("R%d G%d B%d\n",color_pattern[y + j][i + x].r, color_pattern[y + j][i + x].g, color_pattern[y + j][i + x].b);
			move_mouse(wm, x + i, y + j);
			usleep(10000);
		}
	}
	int flag = 0;
	for (int j = 0; j < y; j++)
	{
		flag = 0;
		int i = 0;
		for (i = 0; i < len; i++)
		{
			unsigned long pixel = XGetPixel(img, x + i, y + j);
			Rgb color = convert_pixel_to_rgb(img, pixel);
			color_pattern[y+j][x+i] = color;
			if(color_pattern[y + j][x + i].r == ref[j][i].r
			&& color_pattern[y + j][x + i].g == ref[j][i].g
			&& color_pattern[y + j][x + i].b == ref[j][i].b)
				flag++;
		}
		if (flag == len)
		{
			printf("PATTERN MATCH RETURN 1.\n");
			return 1;
		}
	}
	return 0;
}

void	build_color_matrix(WinManager *wm, Rgb color_matrix[1080][1920])
{
	Rectangle screen_zone = create_rectangle(0, 0, 1920, 1080);
	XImage *screen_image = get_zone_to_check(wm, screen_zone);
	for (int y = 0; y < screen_image->height; y++)
	{
		for (int x = 0; x < screen_image->width; x++)
		{
			unsigned long pixel = XGetPixel(screen_image, x, y);
			Rgb pixel_color = convert_pixel_to_rgb(screen_image, pixel);
			color_matrix[y][x] = pixel_color;
		}
	}
	printf(">>Screen color matrix built.\n");
}

void	build_color_matrix_small(WinManager *wm, Rgb small_matrix[100][100], int x, int y)
{
	int width = 100;
	int height = 100;
	Rectangle screen_zone = create_rectangle(x, y, width, height);
	XImage *screen_image = get_zone_to_check(wm, screen_zone);
	printf(">>screen_reading.c \nbuild_color_matrix_small()\nIMG WIDTH:%d\nIMG HEIGHT:%d\n",screen_image->width, screen_image->height);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned long pixel = XGetPixel(screen_image, i, j);
			Rgb pixel_color = convert_pixel_to_rgb(screen_image, pixel);
			small_matrix[j][i] = pixel_color;
			printf("R:%d G:%d B:%d \n",small_matrix[j][i].r,small_matrix[j][i].g, small_matrix[j][i].b);
			//uncomment these two line bellow to see the matrix building.
			move_mouse(wm, x+i, y+j);
			usleep(100);
		}
	}
	printf("screen_reading.c \nbuild_color_matrix_small()\n>>Small Screen color matrix finish build:<<\n\n");
	printf("TESTING: Sleep 2sec before going on to the next step.\n");
	sleep(2);
}

/* My matrix is build. now I need to check
 * matrix pixel color with pattern
 * lets say my pattern is 253 42 49 (*10)
 * then I need to see if in my matrix I have this pattern.
 *  I set the pattern.
 *  I go through my matrix. I check for the color.
 *  lets try to do it for one pixel only first
 */ 

bool	small_pattern_match(Rgb small_matrix[100][100], Rgb_pattern ref_pattern, Rgb tol)
{
	bool match = true;

	for (int i = 0; i < ref_pattern.width; i++)
	{
		Rgb color = small_matrix[0][i];
		Rgb ref = ref_pattern.color[i];
		printf(">>screen_reading.c  bool small_pattern_match()\nCOLOR - REF:\nTEMP:(R:%d G:%d B:%d) - REF:(R:%d G:%d B:%d)\n\n",  color.r, color.g, color.b, ref.r, ref.g, ref.b);
		if (abs(color.r - ref.r) > tol.r ||
		abs(color.g - ref.g) > tol.g ||
		abs(color.b - ref.b) > tol.b)
		{
			printf("xxNOT MATCHxx\n");
			match = false;
			//break;
		}
		else
			printf(">>MATCH<<\n");
		//usleep(10000);
 	}
	printf("\n");
	return match;
}

int	find_matching_pattern_small(Rgb_pattern ref, int x, int y, Rgb small_matrix[100][100], Point matches[], Rgb tol)
{
	int match_counter = 0;
	int height = 100;
	int width = 100;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < (width - ref.width); i++)
		{
			if (small_pattern_match(small_matrix, ref, tol))
			{
				match_counter++;
				matches[match_counter].x = x + i;
				matches[match_counter].y = y + j;
			}
		}
	}
	printf("Found %d matching pattern<<\n\n", match_counter);
	return match_counter;
}

/* Return 0: count < 40: cannot find ready button on screen.
 * Return 1: count > 40: can find ready button on screen.
 */

int	check_ready_button(WinManager *wm)
{
	Rgb_pattern *ref = create_rgb_pattern(ready_button, 20);
	int x = 1500;
	int y = 800;
	Rgb small_matrix[100][100];
	build_color_matrix_small(wm, small_matrix, x, y);
	Point matches[50];
	Rgb tol = {15, 20, 30};
	int count = find_matching_pattern_small(*ref, x, y, small_matrix, matches, tol);
	if (count > 40)
	{
		printf("Ready button found. COMBAT MODE.\n");
		return 1;
	}
	return 0;	
}

int	check_element(WinManager *wm, Rgb ref, int width, int x, int y, Rgb tol)
{
	Rgb_pattern *ref_pattern = create_rgb_pattern(ref, width);
	Rgb small_matrix[100][100];
	build_color_matrix_small(wm, small_matrix, x, y);
	Point matches[50];
	int count = find_matching_pattern_small(*ref_pattern, x, y, small_matrix, matches, tol);
	if (count < 10)
	{
		printf("%s pattern not found(R:%d G:%d B:%d)\n", ref.color, ref.r, ref.g, ref.b);
		return 0;
	}
	printf("%s pattern found. return 1.\n",ref.color);
	return 1;
}

int	check_color(Rgb ref, int w, int h, Rgb small_matrix[100][100])
{
	Rgb tolerance = {25, 15, 15};
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			for (int k = 0; k < 20; k++)
			{
				Rgb color = small_matrix[j][i+k];
				if (abs(color.r - ref.r) < tolerance.r
				&& abs(color.g - ref.g) < tolerance.g
				&& abs(color.b - ref.b) < tolerance.b)
				{
					printf("RGB PATTERNS OF 20 PIXELS MATCH.\n");
					return 1;
				}
				else
				{
					printf("PATTERNS DONT MATCH\n");
					break;
				}

			}

		}
	}
	printf("NO RGB match in this small matrix.\n");
	return 0;
}

/* now I want to count pattern not single color.
 * so I set a bool to true.
 * I go in the loop of pattern length.
 * true true true true true true true true true true true true true true false > return false
 * true true true true true treu ture true true true ture ture ture ture ture uter treu true treu true true true true true true true true treu true treu treu treu true true true > ok
*/
int	count_match(Rgb ref, Rgb small_matrix[100][100])
{
	int counter = 0;
	for (int j = 0; j < 100; j++)
	{
		for (int i = 0; i < 100; i++)
			counter += check_color(ref, i, j, small_matrix);
	}
	printf("MATCHES:%d\n",counter);
	return (counter);
}
/* 
	>x:1561 y:711 w:100 h:100 (small matrix)
	>RGB Ref: R >= 200 G >= 40 <= 60 B >= 40 <= 50
	>REF: 240 50 45: TOLERANCE: 15
*/
int	check_state(WinManager *wm)
{
	int x = 1561;
      	int y = 711;
	static Rgb small_matrix[100][100];
	build_color_matrix_small(wm, small_matrix, x, y);
	//Point pattern_list[100];
	//Rgb *icon_pattern = create_rgb_pattern(red_arrow_icon);;
	Rgb ref = {40, 40, 40};
	//small_pattern_match(small_matrix, icon_pattern, red_arrow_icon.len);
//	int matches = find_matching_pattern_small(icon_pattern, x, y, small_matrix, icon_pattern->len, 15, pattern_list);
	int matches = count_match(ref, small_matrix);
	return 1;
}

void	build_color_matrix_vertical(WinManager *wm, Rgb color_matrix_v[1920][1080])
{
	Rectangle screen_zone = create_rectangle(0, 0, 1920, 1080);
	XImage *screen_image = get_zone_to_check(wm, screen_zone);
	for (int x = 0; x < screen_image->width; x++)
	{
		for (int y = 0; y < screen_image->height; y++)
		{
			unsigned long pixel = XGetPixel(screen_image, x, y);
			Rgb pixel_color = convert_pixel_to_rgb(screen_image, pixel);
			color_matrix_v[x][y] = pixel_color;
		}
	}
	printf(">>Screen color VERTICAL matrix built.\n");
}

bool	pattern_match_vertical(Rgb color_matrix_v[1920][1080], Rgb *ref_color_pattern, int pattern_len, int x, int y)
{
	bool matching_pattern = true;
	int tolerance = 9;
	for (int i = 0; i < pattern_len; i++)
	{
		Rgb color = color_matrix_v[x][y + i];
		Rgb ref = ref_color_pattern[i];
		if (abs(color.r - ref.r) > tolerance ||
		abs(color.g - ref.g) > tolerance ||
		abs(color.b - ref.b) > tolerance)
		{
			matching_pattern = false;
			break;
		}
	}
	return matching_pattern;
}

int	find_matching_pattern_v(Rgb *ref_color_pattern, Rgb color_matrix_v[1920][1080], int pattern_len, Point matches[])
{
	int match_count = 0;
	for (int x = 0; x < 1920; x++)
	{
		for (int y = 0; y < 1080 - pattern_len; y++)
		{
			if (pattern_match_vertical(color_matrix_v, ref_color_pattern, pattern_len, x, y))
			{
				int mx = matches[match_count].y = y;
				int my = matches[match_count].x = x;
				y+= 20;
				x+= 10;
				printf("Matching pattern in (%d, %d)\n", mx, my);
				match_count++;
			}
		}
	}
	printf(">>find_match_pat_c()\nFound:%dmatching pattern\n", match_count);
	return match_count;
}

bool	color_difference(Rgb ref, Rgb color, Rgb difference, Rgb tolerance)
{
	difference.r = (abs(color.r - ref.r));
	difference.g = (abs(color.g - ref.g));
	difference.b = (abs(color.b - ref.b));
	if (difference.r > tolerance.r || difference.g > tolerance.g || difference.b > tolerance.b)
		return (false);
	return (true);
}

bool	pattern_match(Rgb color_matrix[1080][1920], Rgb *ref_color_pattern, int pattern_length, int x, int y, int tolerance)
{
	bool matching_pattern = true;
	for (int i = 0; i < pattern_length; i++)
	{
		Rgb color = color_matrix[y][x + i];
		Rgb ref = ref_color_pattern[i];
		if (abs(color.r - ref.r) > tolerance ||
		abs(color.g - ref.g) > tolerance ||
		abs(color.b - ref.b) > tolerance)
		{
			matching_pattern = false;
			break;
		}
	}
	return matching_pattern;
}

int	find_matching_pattern(Rgb *ref_color_pattern, Rgb color_matrix[1080][1920], int pattern_length, int tolerance, Point matches[])
{
	int	match_counter = 0;
	for (int y = 0; y < 1080; y++)
	{
		for (int x = 0; x < 1920 - pattern_length; x++)
		{
			if (pattern_match(color_matrix, ref_color_pattern, pattern_length, x, y, tolerance))
			{
				matches[match_counter].x = x;
				matches[match_counter].y = y;
				match_counter++;
			}
		}
	}
	printf("Found %d matching pattern\n", match_counter);
	return match_counter;
}


Rectangle build_po_zone(Point p)
{
	int left = p.x - HALF_PO_W;
	int right = p.x + HALF_PO_W;
	int top = p.y - HALF_PO_H;
	int bottom = p.y + HALF_PO_H;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right >= FIGHT_W) right = FIGHT_W - 1;
	if (bottom >= FIGHT_H) bottom = FIGHT_H - 1;

	return create_rectangle(left, top, right - left +1, bottom - top + 1);
}

int find_matching_pattern_in_rect(Rgb *ref, int pattern_len, int tol,
                                  Rgb matrix[1080][1920], Rectangle r,
                                  Point matches[], int max_match)
{
	Point p = find_player(matrix, red_color_pattern, 30, 4);
	int count = 0;

	/* 1) si la fenêtre est plus petite que le pattern, aucun match possible */
	if (r.width  < pattern_len) return 0;

	for (int y = r.y; y < r.y + r.height; ++y) {
		for (int x = r.x; x <= r.x + r.width - pattern_len; ++x) {

			if (pattern_match(matrix, ref, pattern_len, x, y, tol)) {
				if (count < max_match) {          // sécurise le buffer
					matches[count++] = (Point){x, y};
					printf("Tile in PLAYER PO %d %d\n",  matches[count].x, matches[count].y);
					printf("pattern match\n");
				}
			}
		}
	}
	return count;
}

Point	find_player(Rgb color_matrix[1080][1920], Rgb *ref_color_pattern, int pixel_pattern_length, int tolerance)
{
	Point player_pos;
	int same_pattern_counter = 0;
	bool match = false;
	for (int y = 0; y  < 790; y++)
	{
		for (int x = 0; x < 1850 - pixel_pattern_length; x++)
		{
			match = true;
			for (int i = 0; i < pixel_pattern_length; i++)
			{
				Rgb pixel = color_matrix[y][x + i];
				Rgb ref = ref_color_pattern[i];
				if  (abs(pixel.r - ref.r) > tolerance
				|| abs(pixel.g - ref. g) > tolerance
				|| abs(pixel.b - ref.b) > tolerance)
				{
					match = false;
					break;
				}
			}
			if (match)
			{
				same_pattern_counter++;
				player_pos.x = x + 18;
				player_pos.y = y - 14;
			}
		}
	}
	if (same_pattern_counter < 1)
	{
		printf("COULD NOT FIND ANY PLAYER'S COLOR PATTERN: RETURNING CENTER OF SCREEN COORDINATES\n");
		Point center;
		center.x = 1920/2;
		center.y = 1080/2;
		sleep(4);
		return center;
	}
	printf("PLAYER POS: [%d, %d]\n", player_pos.x, player_pos.y);
	return player_pos;
}

Point	find_enemy(Rgb color_matrix[1080][1920], Rgb *ref_color_pattern, int pixel_pattern_length, int tolerance)
{
	Point enemy_pos;
	int same_pattern_counter = 0;
	bool match = false;
	for (int y = 0; y  < 770; y++)
	{
		for (int x = 0; x < 1850 - pixel_pattern_length; x++)
		{
			match = true;
			for (int i = 0; i < pixel_pattern_length; i++)
			{
				Rgb pixel = color_matrix[y][x+i];
				Rgb ref = ref_color_pattern[i];
				if  (abs(pixel.r - ref.r) > tolerance
				|| abs(pixel.g - ref. g) > tolerance
				|| abs(pixel.b - ref.b) > tolerance)
				{
					match = false;
					break;
				}
			}
			if (match)
			{
				same_pattern_counter++;
				enemy_pos.x = x + 18;
				enemy_pos.y = y - 14;
			}
		}
	}
	if (same_pattern_counter < 1)
	{
		printf("COULD NOT FIND ANY ENEMY MATCHING PATTERN MATCH : RETURN POINT IN CENTER OF SCREEN\n");
		Point center;
		center.x = 1920/2;
		center.y = 1080/2;
		sleep(4);
		return center;
	}
	printf("ENEMY POS: [%d, %d]\n", enemy_pos.x, enemy_pos.y);
	return enemy_pos;
}

int	get_red_square_pos(Rgb color_matrix[1080][1920], int pixel_pattern_length, int tolerance, Point player_pos, Point enemy_pos, Point red_square[])
{
	Rgb red_square_color_pattern[pixel_pattern_length];
	int red_square_counter = 0;
	bool match = false;
	Point red_square_pos;
	for (int i = 0; i < pixel_pattern_length; i++)
	{
		red_square_color_pattern[i].r = 255;
		red_square_color_pattern[i].g = 0;
		red_square_color_pattern[i].b = 0;
	}
	for (int y = 0; y  < 800; y++)
	{
		for (int x = 0; x < 1920 - pixel_pattern_length; x++)
		{
			match = true;
			for (int i = 0; i < pixel_pattern_length; i++)
			{
				Rgb pixel = color_matrix[y][x+i];
				Rgb ref = red_square_color_pattern[i];
				if  (abs(pixel.r - ref.r) > tolerance
				|| abs(pixel.g - ref. g) > tolerance
				|| abs(pixel.b - ref.b) > tolerance)
				{
					match = false;
					break;
				}
			}
			if (match)
			{
				red_square[red_square_counter].x = x + (pixel_pattern_length / 2);
				red_square[red_square_counter].y = y;
				red_square_counter++;
				red_square_pos.x = x + (pixel_pattern_length / 2);
				red_square_pos.y = y;
			}
		}
	}
	if (red_square_counter < 1)
	{
		printf("COULD NOT FIND ANY RED SQUARE ON MAP\n");
		return red_square_counter;
	}
	return red_square_counter;
}

/* get_grey_tiles() return the number of grey tiles in the current screen,
 * populate a Point list with all the grey tiles coordinates 
 * We will use grey_tile[] as an parameter in order to move into the map.
 * PATTERN MESURE : LIGHT GREY 93 DARK GREY : 92
 */
int	get_grey_tiles(Rgb color_matrix[1080][1920], int pattern_len, int tolerance, Point grey_tile[])
{
	Rgb light_grey_tile_pattern[pattern_len];
	Rgb dark_grey_tile_pattern[pattern_len];
	int tile_counter = 0;
	int match = 0;

	for (int i = 0; i < pattern_len; i++)
	{
		light_grey_tile_pattern[i].r = 131;
		light_grey_tile_pattern[i].g = 135;
		light_grey_tile_pattern[i].b = 141;

		dark_grey_tile_pattern[i].r = 121;
		dark_grey_tile_pattern[i].g = 125;
		dark_grey_tile_pattern[i].b = 131;
	}
	Point grey_tile_pos;
	for (int y = 0; y  < 791; y++)
	{
		for (int x = 0; x < 1359 - pattern_len; x++)
		{
			match = 0;
			for (int i = 0; i < pattern_len; i++)
			{
				Rgb pixel = color_matrix[y][x+i];
				Rgb light_ref = light_grey_tile_pattern[i];
				Rgb dark_ref = dark_grey_tile_pattern[i];

				if (abs(pixel.r - light_ref.r) < tolerance
				&& abs(pixel.g - light_ref.g) < tolerance
				&& abs(pixel.b - light_ref.b) < tolerance)
				{
					match++;
				}
				else if (abs(pixel.r - dark_ref.r) < tolerance
				&& abs(pixel.g - dark_ref.g) < tolerance
				&& abs(pixel.b - dark_ref.b) < tolerance)
				{
					match++;
				}
				else
					break;
			}
			if (match == pattern_len)
			{
				grey_tile[tile_counter].x = x + (pattern_len/ 2);
				grey_tile[tile_counter].y = y;
				tile_counter++;
				grey_tile_pos.x = x + (pattern_len / 2);
				grey_tile_pos.y = y;
			}
		}
	}
	printf("FOUND A TOTAL OF %d TILES ACROSS THE SCREEN\n", tile_counter);
	if (tile_counter < 1)
	{
		printf("COULD NOT FIND ANY TILE ON MAP\n");
		return tile_counter;
	}
	printf("TILES POS: [%d, %d]\n", grey_tile_pos.x, grey_tile_pos.y);
	return tile_counter;
}

// pattern length : 93
int	get_light_grey_tiles(Rgb color_matrix[1080][1920], int pattern_len, int tolerance, Point grey_tile[])
{
	Point grey_tile_pos;
	Rgb light_grey_tile_pattern[pattern_len];
	int tile_counter = 0;
	bool match = false;
	for (int i = 0; i < pattern_len; i++)
	{
		light_grey_tile_pattern[i].r = 131;
		light_grey_tile_pattern[i].g = 135;
		light_grey_tile_pattern[i].b = 141;

	}
	for (int y = 0; y  < 790; y++)
	{
		for (int x = 0; x < 1800 - pattern_len; x++)
		{
			match = true;
			for (int i = 0; i < pattern_len; i++)
			{
				Rgb pixel = color_matrix[y][x+i];
				Rgb light_ref = light_grey_tile_pattern[i];

				if (abs(pixel.r - light_ref.r) > tolerance
				|| abs(pixel.g - light_ref.g) > tolerance
				|| abs(pixel.b - light_ref.b) > tolerance)
				{
					match = false;
					break;
				}
			}
			if (match) 
			{
				grey_tile[tile_counter].x = x + (pattern_len/ 2);
				grey_tile[tile_counter].y = y;
				tile_counter++;
				grey_tile_pos.x = x + (pattern_len / 2);
				grey_tile_pos.y = y;
			}
		}
	}
	printf("FOUND A TOTAL OF %d LIGHT TILES ACROSS THE SCREEN\n", tile_counter);
	if (tile_counter < 1)
	{
		printf("COULD NOT FIND ANY LIGHT TILE ON MAP\n");
		return tile_counter;
	}
	return tile_counter;
}

/* pattern length pour les dark : 92 */
int	get_dark_grey_tiles(Rgb color_matrix[1080][1920], int pattern_len, int tolerance, Point grey_tile[])
{
	Point grey_tile_pos;
	Rgb dark_grey_tile_pattern[pattern_len];
	int tile_counter = get_light_grey_tiles(color_matrix, pattern_len, tolerance, grey_tile);
	bool match = false;

	for (int i = 0; i < pattern_len; i++)
	{
		dark_grey_tile_pattern[i].r = 118;
		dark_grey_tile_pattern[i].g = 122;
		dark_grey_tile_pattern[i].b = 127;
	}
	for (int y = 0; y  < 791; y++)
	{
		for (int x = 0; x < 1800 - pattern_len; x++)
		{
			match = true;
			for (int i = 0; i < pattern_len; i++)
			{
				Rgb pixel = color_matrix[y][x+i];
				Rgb dark_ref = dark_grey_tile_pattern[i];

				if (abs(pixel.r - dark_ref.r) > tolerance
				|| abs(pixel.g - dark_ref.g) > tolerance
				|| abs(pixel.b - dark_ref.b) > tolerance)
				{
					match = false;
					break;
				}
			}
			if (match)
			{
				grey_tile[tile_counter].x = x + (pattern_len/ 2);
				grey_tile[tile_counter].y = y;
				tile_counter++;
				grey_tile_pos.x = x + (pattern_len / 2);
				grey_tile_pos.y = y;
			}
		}
	}
	printf("FOUND A TOTAL OF %d DARK TILES ACROSS THE SCREEN\n", tile_counter);
	if (tile_counter < 1)
	{
		printf("COULD NOT FIND ANY DARK TILE ON MAP\n");
		return tile_counter;
	}
	return tile_counter;
}

// this function will return the smallest distance between player enemy
// it will go through each red square and do the difference with enemy x and y
// it takes a list of red square,its size and the enemy position
Point	find_closest_placement_to_enemy(Point red_square[], int size, Point enemy_pos)
{
	Point placement = red_square[0];
	int smallest_distance = 69696969;
	for (int i = 0; i < size; i++)
	{
		int distance = abs(red_square[i].x - enemy_pos.x) + abs(red_square[i].y - enemy_pos.y);
		if (distance < smallest_distance)
			{
				smallest_distance = distance;
				placement = red_square[i];
			}
	}
	printf("SMALLEST DISTANCE BETWEEN PLAYER AND ENEMY LOCATED IN : (%d, %d)\n", placement.x, placement.y);
	return placement;
}

int	check_movement_point(WinManager *wm, int tolerance)
{
	Rectangle movement_point_zone = create_rectangle(1151, 893, 2, 1);
	XImage* movement_point_image = get_zone_to_check(wm, movement_point_zone);
	Rgb zero_mp_color[3] = {{.r = 0, .g = 102, .b = 0}, {.r = 231, .g = 231, .b = 231}, {.r = 231, .g = 231, .b = 231}};
	int zero_mp_counter = 0;
	Rgb one_mp_color[3] = {{.r = 155, .g = 166, .b = 155}, {.r = 0, .g = 102, .b = 0}, {.r = 0, .g = 102, .b = 0}};
	int one_mp_counter = 0;
	Rgb two_mp_color[3] = {{.r = 0, .g = 102, .b = 0}, {.r = 231, .g = 231, .b = 231}, {.r = 0, .g = 102, .b = 0}};
	int two_mp_counter = 0;
	Rgb three_mp_color[3] = {{.r = 0, .g = 102, .b = 0}, {.r = 0, .g = 102, .b = 0}, {.r = 0, .g = 102, .b = 0}};
	int three_mp_counter = 0;

	for (int y = movement_point_zone.height; y < movement_point_zone.y; y++)
	{
		for (int x = movement_point_zone.width; x < movement_point_zone.x; x++)
		{
			unsigned long pixel = XGetPixel(movement_point_image, x, y);
			Rgb pixel_color = convert_pixel_to_rgb(movement_point_image, pixel);
			for (int i = 0; i < 3; i++)
			{
				if (abs(pixel_color.r - zero_mp_color[i].r) < tolerance 
				&& abs(pixel_color.g - zero_mp_color[i].g) < tolerance
				&& abs(pixel_color.b - zero_mp_color[i].b) < tolerance)
				{
					zero_mp_counter++;
					{
						if (zero_mp_counter == 3)
						{
							printf("0 PM LEFT\n");
							return 0;
						}
					}
				}
				else if (abs(pixel_color.r - one_mp_color[i].r) < tolerance 
				&& abs(pixel_color.g - one_mp_color[i].g) < tolerance
				&& abs(pixel_color.b - one_mp_color[i].b) < tolerance)
				{
					one_mp_counter++;
					{
						if (one_mp_counter == 3)
						{
							printf("1 PM LEFT\n");
							return 1;
						}
					}
				}
				else if (abs(pixel_color.r - two_mp_color[i].r) < tolerance 
				&& abs(pixel_color.g - two_mp_color[i].g) < tolerance
				&& abs(pixel_color.b - two_mp_color[i].b) < tolerance)
				{
					two_mp_counter++;
					{
						if (two_mp_counter == 3)
						{
							printf("2 PM LEFT\n");
							return 2;
						}
					}
				}
				else if (abs(pixel_color.r - three_mp_color[i].r) < tolerance 
				&& abs(pixel_color.g - three_mp_color[i].g) < tolerance
				&& abs(pixel_color.b - three_mp_color[i].b) < tolerance)
				{
					three_mp_counter++;
					{
						if (three_mp_counter == 3)
						{
							printf("3 PM LEFT\n");
							return 3;
						}
					}
				}
			}
		}
	}
	return -1;
}

int	is_my_turn(WinManager *wm)
{
	Rectangle turn_zone = create_rectangle (1109, 894, 16, 8);
	XImage *turn_image = get_zone_to_check(wm, turn_zone);
	if (check_orange_context_menu_color(turn_image, orange_button, 3) > 30)
	{
		printf("Orange find in 1109, 894 : It's your turn !\n");
		return 1;
	}
	printf("COULD NOT FIND ORANGE IN THE ORANGE CIRCLE IT IS NOT YOUR TURN\n");
	return 0;
}

// capture la zone de l'ecran a comparer
// extrait la suite de Rgb a comparer
// compare avec pattern_match

int	compares_rgb_sequences(WinManager *wm, Rgb *ref_pattern, int pattern_len, Rectangle zone_r, int tolerance)
{
	// capture de la zone de l'ecran
	XImage *img = get_zone_to_check(wm, zone_r);
	if (!img)
	{
		fprintf(stderr, "comapre_rgb_sequences : XGetImage failed\n");
		return 0;
	}

	// copie de la zone danns un tableau temp[]
	Rgb temp[pattern_len];
	for (int i = 0; i < pattern_len; i++)
	{
		unsigned long px = XGetPixel(img, i, 0);
		temp[i] = convert_pixel_to_rgb(img, px);
	}
		
	// simule de la matrice (cast)
	Rgb (*row)[1920] = (Rgb (*)[1920])temp;
	bool match_found = pattern_match(row, ref_pattern, pattern_len, 0, 0, tolerance);
	return match_found ? 1 : 0;
}

int	check_enemy_life(WinManager *wm, Rgb color_matrix[1080][1920])
{
	Rectangle life_zone = create_rectangle(1556, 836, 6, 1);
	int life_bar_match = compares_rgb_sequences(wm, blue_color_pattern, 6, life_zone, 3);
	if (life_bar_match){
		printf("ENEMY DEAD\n");
		return 0;
	}
	else 
	{
		printf("ENEMY ALIVE\n");
		return 1;
	}
}

int end_of_fight(WinManager *wm)
{
	int tolerance = 3;
	Rectangle r = create_rectangle(1326, 723, 1, 1);
	XImage* img = get_zone_to_check(wm, r);
	unsigned long pixel = XGetPixel(img, 0, 0);
	Rgb rgb = convert_pixel_to_rgb(img, pixel);
	if (abs(rgb.r - 255 ) > tolerance)
	{
		printf("Cannot see the end combat window\n");
		return 0;
	}
	else
	{
		printf("End fight window spoted\n");
		return 1;
	}
	return 0;
}

