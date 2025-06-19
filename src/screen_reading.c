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

Rgb_pattern	create_rgb_pattern(Rgb color, int height, int width)
{
	Rgb_pattern color_pattern;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			color_pattern.color = color;
		}
	}
	return color_pattern;
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
	int red_shift, green_shift, blue_shift = 0;
	red_shift = get_bit_shift(zone_to_check->red_mask);
	green_shift = get_bit_shift(zone_to_check->green_mask);
	blue_shift = get_bit_shift(zone_to_check->blue_mask);
	rgb.r = (pixel & zone_to_check->red_mask) >> red_shift;
	rgb.g = (pixel & zone_to_check->green_mask) >> green_shift;
	rgb.b = (pixel & zone_to_check->blue_mask) >> blue_shift;
	return rgb;
}

// need to compare a sequence of pixel_rgb in a given zone


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

int	ready_button_visible(WinManager *wm)
{
	static Rgb color_matrix[1080][1920];
	build_color_matrix(wm, color_matrix);
	Rectangle ready_button_zone = create_rectangle(1520, 800, 100, 30);
	int x = ready_button_zone.x;
	int y = ready_button_zone.y;
	XImage *ready_img = get_zone_to_check(wm, ready_button_zone);
	printf("checking if in combat ...\n");
	if (!ready_img)
		printf("NO IMAGE\n");
	unsigned long pixel = XGetPixel(ready_img, x, y);
	printf("Pixel:%ld\n",pixel);
	Rgb color = convert_pixel_to_rgb(ready_img, pixel);
	printf("REF COLOR: R:%d G:%d B:%d\n", color.r, color.g, color.b);
	printf("scaning zone...\n");
	for (int j = 0; j < 30; j++)
	{
		for (int i = 0; i < 30; i++)
		{
			move_mouse(wm, x+i, y+j);
			usleep(10000);
		}
	}
	for (int j = 1; j < 30; j++)
	{
		int flag = 0;	
		for (int i = 1; i < 30; i++)
		{
			unsigned long tmp_pixel = XGetPixel(ready_img, x + i, y + j);
			Rgb pixel_color = convert_pixel_to_rgb(ready_img, tmp_pixel);
			printf("COLOR IN (%d %d)R:%d G:%d B:%d\n", x + i, y + j, pixel_color.r, pixel_color.g, pixel_color.b);
			if (pixel_color.r == color.r && pixel_color.g == color.g && pixel_color.b == color.b
			&& pixel_color.r > 250 && pixel_color.b > 125 && pixel_color.b < 200 && pixel_color.g < 40)
			{
				printf("flag trigger\n");
				flag++;
			}
		}
		printf("Flag trigger >%d< times\n", flag);
		if (flag > 25)
		{
			printf("Same COLOR PATTERN FOUND 25 times. Return\n");
			return 1;
		}
	}
	return 0;
}

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
	sleep(4);
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
	//temporary set from 100 to 10 for testing purpose
	int width = 10;
	int height = 10;
	Rectangle screen_zone = create_rectangle(x, y, width, height);
	XImage *screen_image = get_zone_to_check(wm, screen_zone);
	printf("screen_reading.c <l719>\nbuild_color_matrix_small()\nIMG created: IMG WIDTH:%d\nIMG HEIGHT:%d\n",screen_image->width, screen_image->height);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned long pixel = XGetPixel(screen_image, i, j);
			Rgb pixel_color = convert_pixel_to_rgb(screen_image, pixel);
			small_matrix[y + j][x + i] = pixel_color;
			printf("R:%d G:%d B:%d\n",small_matrix[y+j][x+i].r,
			small_matrix[y+j][x+i].g, small_matrix[y+j][x+i].b);
			move_mouse(wm, x+i, y+j);
			usleep(1000);
		}
	}
	printf("screen_reading.c <l733>\nbuild_color_matrix_small()\n>>Small Screen color matrix finish build:\n");
}

bool	small_pattern_match(Rgb small_matrix[100][100], Rgb *ref_pattern, int pattern_len, int x, int y)
{
	int tolerance = 5;
	bool match = true;
	for (int i = 0; i < pattern_len; i++)
	{
		Rgb color = small_matrix[y][x+i];
		Rgb ref = ref_pattern[i];
		printf("screen_reading.c<l744>\nbool small_pattern_match()\nCOLOR - REF:\nTEMP:(R:%d G:%d B:%d) - REF:(R:%d G:%d B:%d)\n",  color.r, color.g, color.b, ref.r, ref.g, ref.b);
		if (abs(color.r - ref.r) > tolerance ||
		abs(color.g - ref.g) > tolerance ||
		abs(color.b - ref.b) > tolerance)
		{
			printf("xxNOT MATCHxx\n");
			match = false;
			break;
		}
		printf(">>MATCH<<\n");
	}
	return match;
}

int	find_matching_pattern_small(Rgb *ref_color_pattern, int y, int x, Rgb small_matrix[100][100], int pattern_length, int tolerance, Point matches[])
{
	int	match_counter = 0;
	//temporary set from 100 to 10 for testing purpose
	int height = 10;
	int width = 10;
	for (int j = 0; j < height; j++)
	{
		printf("screen_reading.c<l763>\nfind_matching_pattern_small()\nScaning line comparing pattern...\n");
		for (int i = 0; i < width - pattern_length; i++)
		{
			if (small_pattern_match(small_matrix, ref_color_pattern, pattern_length, x, y))
			{
				matches[match_counter].y = y + j;
				matches[match_counter].x = x + i;
				printf("y + j = %d + %d = %d\n", y, j, y + j);
				printf("x + i = %d + %d = %d\n", x, i, x + i);
				match_counter++;
			}
		}
	}
	printf("Found %d matching pattern\n", match_counter);
	return match_counter;
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

