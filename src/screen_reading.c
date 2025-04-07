#include "screen_reading.h"
#include "window_manager.h"
#include <stdlib.h>
#include <unistd.h>

Rgb orange_button = {.r = 230, .g = 87, .b = 0};

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
	/*
	for (int i = 0; i < n; i++)
	{
		x += 300;
		y += 250;
		zones_to_check[i] = XGetImage(wm->display,
		wm->root,
		x,
		y,
		width,
		height,
		AllPlanes,
		ZPixmap);
	}
	*/
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

Rgb*	get_color_in_frame(XImage *zone_to_check)
{
	Rgb *rgb;
	if (!zone_to_check)
	{
		printf("could not define zone\n");
		return NULL;
	}
	printf("IMG WIDTH:%d \nIMG HEIGHT:%d\nIMG DEPTH:%d\n", 
	zone_to_check->width, zone_to_check->height, zone_to_check->depth);
	for (int i = 0; i < zone_to_check->height ; i++)
	{
		for (int j = 0; j < zone_to_check->width ; j++)
		{
			unsigned long pixel = XGetPixel(zone_to_check, j, i);
			Rgb* rgb = convert_pixel_to_rgb(zone_to_check, pixel);
			printf("(%d, %d): R%d G%d B%d %ld\n",
			(j), (i), rgb->r, rgb->g, rgb->b, pixel);
		}
	}
	return rgb;
}

int	check_orange_color(XImage *zone_to_check)
{
	// pour la frame 1
	// on a un counter de orange
	// pour check il faut : avoir un color code qu'on recupere grace a RGB* convert p()
	// mais il nous les faut pour toute la zone : il nous faut comparer 100 codes
	int orange_counter = 0;
	
	for (int i = 0; i < zone_to_check->height ; i++)
	{
		for (int j = 0; j < zone_to_check->width ; j++)
		{
			unsigned long pixel = XGetPixel(zone_to_check, j, i);
			Rgb* rgb = convert_pixel_to_rgb(zone_to_check, pixel);
			// si notre pixel est de couleur orange, increment orange counter
			// for loop ?
			if (rgb->r == orange_button.r && rgb->g == orange_button.g &&
			rgb->b == orange_button.b)
				orange_counter++;
		}
	}
	
	if (orange_counter > 9)
	{
		printf("ORANGE BUTTON IN CENTER OF SCREEN\n");
		return 1;
	}
	printf("ORANGE PIXEL:%d\n", orange_counter);
	return 0;
}

int	compare_colors(Rgb *a, Rgb *b)
{
	int same_frame = 0;
	for (int i = 0; i < 100; i++)
	{
		if (a[i].r == b[i].r && a[i].g == b[i].g && a[i].b == b[i].b)
		{
			same_frame++;
			printf("Color match\n");
		}
		else
			printf("Different color\n");
	}
	if (same_frame < 80)
		return 0;
	printf("FRAME MATCHING : %d\n", same_frame);
	return 0;
}

int	check_frame(XImage **zones_to_check, int n_zone)
{
	Rgb *colors_zone_1;
	printf("COLORS IN FRAME 1, 1ST ZONE:\n");
	colors_zone_1 = get_color_in_frame(zones_to_check[0]);
	Rgb *colors_zone_2;
	printf("COLORS IN FRAME 1, 2ND ZONE:\n");
	colors_zone_2 = get_color_in_frame(zones_to_check[1]);
	
	sleep(5);

	Rgb *temp_colors_zone_1;
	printf("COLORS IN FRAME 2 1ST ZONE:\n");
	temp_colors_zone_1 = get_color_in_frame(zones_to_check[0]);
	Rgb *temp_colors_zone_2;
	printf("COLORS IN FRAME 2 2ND ZONE:\n");
	temp_colors_zone_2 = get_color_in_frame(zones_to_check[1]);

	compare_colors(colors_zone_1, temp_colors_zone_1);
	compare_colors(colors_zone_2, temp_colors_zone_2);
	
	// current rgb :	
	// rgb est un tableau de struct ?
	// rgb_zone_1[100] -> rgb.r[0...], rgb.g[0...], rgb.b[0...]
	// rgb_zone_2[100] -> rgb.r[0...], rgb.g[0...], rgb.b[0...]
	// get rgb_zone 1 - quel form
	// on a 100 valeurs a comparer
	// get rgb zone 2

	//sleep 10s
	//creer temp rgb 
	// get rgb_zone 1
	// get rgb zone 2
	// for i = 0 ; i < 100; i++
	//	if (rgb_zone_1[i].rgb.r == temp_zone_1[i].rgb.r)
	//		print samecolor
	// for i = 0 
	// meme logique pour les deux autres codes couleurs gb
	// if rgb_zone_1[0].rgb.r == temp_rgb_zone_1[0]
	// repeat (get rgbzone*)


	// get
	return 0;
}

// releve la couleur recherche sur la zone
// on peut faire un carre de 10*10 
// si la couleur correspond a la couleur du ble 
// click sur les coordonnes (x y)
// sinon en deduire la current frame

