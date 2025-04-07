#include "screen_reading.h"
#include "window_manager.h"
#include "event_handler.h"
#include <stdlib.h>
#include <unistd.h>

Rgb orange_button = {.r = 230, .g = 87, .b = 0};
Rgb log_in_button = {.r = 242, .g = 146, .b = 0};
// Rgb wheat

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

XImage	**get_nzone(WinManager *wm, int n)
{
	XImage **zones_to_check = malloc(n * sizeof(XImage*));
	int x = 300;
	int y = 250;
	unsigned int width = 10;
	unsigned int height = 10;
	Rectangle rectangle[n];
	for (int i = 0; i < n; i++)
	{
		rectangle[i] = create_rectangle(x, y, width, height);
		printf("Rectangle %d: x=%d y=%d w=%u h=%u\n", i, rectangle[i].x, rectangle[i].y, rectangle[i].width, rectangle[i].height);
		x+=300;
		y+=250;
		zones_to_check[i] = get_zone_to_check(wm, rectangle[i]);
		if (zones_to_check[i] == NULL)
		{
			printf("COULD NOT ALLOCATE MEM AT IMAGE %d\n", i);
			return NULL;
		}
	}
	return zones_to_check;
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

Rgb*	get_color_in_frame(WinManager *wm, XImage *zone_to_check)
{
	Rgb *rgb;
	if (!zone_to_check)
	{
		printf("could not define zone\n");
		return NULL;
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
	return rgb;
}

int	check_log_in(XImage *zone_to_check)
{
	int orange_counter = 0;
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
				orange_counter++;
		}
	}
	if (orange_counter > 30)
	{
		printf("LOG IN BUTTON IN ZONE\n");
		return 1;
	}
	else
		printf("No button\n");
	return 0;
}

int	check_orange_color(XImage *zone_to_check)
{
	int orange_counter = 0;
	int tolerance = 10;
	for (int i = 0; i < zone_to_check->height ; i++)
	{
		for (int j = 0; j < zone_to_check->width ; j++)
		{
			unsigned long pixel = XGetPixel(zone_to_check, j, i);
			Rgb rgb = convert_pixel_to_rgb(zone_to_check, pixel);
			if (abs(rgb.r - orange_button.r) < tolerance
			&& abs(rgb.g - orange_button.g) < tolerance
			&& abs(rgb.b - orange_button.b) < tolerance)
				orange_counter++;
		}
	}
	if (orange_counter > 30)
	{
		printf("ORANGE BUTTON IN ZONE\n");
		return 1;
	}
	else
		printf("No button\n");
	return 0;
}

int	compare_colors(XImage *zone_to_check_a, XImage *zone_to_check_b)
{
	int same_frame = 0;
	int tolerance = 10;
	int match_counter = 0;
	for (int i = 0; i < zone_to_check_a->height; i++)
	{
		for (int j = 0; j < zone_to_check_a->width ; j++)
		{
			unsigned long pixel_a = XGetPixel(zone_to_check_a, j, i);
			unsigned long pixel_b = XGetPixel(zone_to_check_b, j, i);
			Rgb rgb_a = convert_pixel_to_rgb(zone_to_check_a, pixel_a);
			Rgb rgb_b = convert_pixel_to_rgb(zone_to_check_b, pixel_b);
			printf("(%d, %d): R%d G%d B%d %ld\n",
			(j), (i), rgb_a.r, rgb_a.g, rgb_a.b, pixel_a);
			printf("(%d, %d): R%d G%d B%d %ld\n",
			(j), (i), rgb_b.r, rgb_b.g, rgb_b.b, pixel_b);
			if (abs(rgb_a.r - rgb_b.r) < tolerance &&
			abs(rgb_a.g - rgb_b.g) < tolerance &&
			abs(rgb_a.b - rgb_b.b) < tolerance)
			{
				match_counter++;
				printf("PIXEL MATCH\n");
			}
			else
				printf("PIXEL DOES NOT MATCH\n");
		}
	}
	if (match_counter < 90)
	{
		printf("FRAMES DONT MATCH\n");
		return 1;
	}
	else
	{
		printf("FRAMES MATCH\n");
		return 0;
	}
}

int	check_frame(WinManager *wm)
{
	Rectangle r_a = create_rectangle(400, 150, 200, 100);
	Rgb *colors_zone_one;
	printf("COLORS IN FRAME 1 1ST ZONE:\n");
	XImage *zone_one_frame_one = get_zone_to_check(wm, r_a);
	//printf("COLORS IN FRAME 1, 2ND ZONE:\n");
	Rectangle r_b = create_rectangle(1100, 600, 300, 400);
	Rgb *colors_zone_two;
	XImage *zone_two_frame_one = get_zone_to_check(wm, r_b);
	sleep(4);
	XSync(wm->display, False);
	Rgb *temp_colors_zone_one;
	printf("COLORS IN FRAME 2 1ST ZONE:\n");
	XImage *zone_one_frame_two = get_zone_to_check(wm, r_a);
	Rgb *temp_colors_zone_two;
	//printf("COLORS IN FRAME 2 2ND ZONE:\n");
	//temp_colors_zone_2 = get_color_in_frame(zones_to_check[1]);

	compare_colors(zone_one_frame_one, zone_one_frame_two);
	// can return 0 1 2 3 according to the current frame we are
	return 0;
}

int	log_in(WinManager *wm)
{
	Rectangle orange_r = create_rectangle(1000, 650, 10, 10);
	XImage *orange_button_zone = get_zone_to_check(wm, orange_r);
	Rectangle log_r = create_rectangle(600, 500, 10, 10);
	XImage *log_zone = get_zone_to_check(wm, log_r);
	if (check_log_in(log_zone) == 1)
		click_log_button(wm);
	sleep(1);
	start(wm);
	// check_zone_pour voir si en jeu
	return 0;
}

// releve la couleur recherche sur la zone
// on peut faire un carre de 10*10 
// si la couleur correspond a la couleur du ble 
// click sur les coordonnes (x y)
// sinon en deduire la current frame
