#include "types.h"
#include <stdlib.h>
#include <unistd.h>
#include "screen_reading.h"
#include "event_handler.h"
#include "window_manager.h"

Rgb orange_button = {.r = 255, .g = 102, .b = 0};
Rgb log_in_button = {.r = 242, .g = 146, .b = 0};
Rgb wheat = {.r = 56, .g = 62, .b = 15};

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

Rgb wheat_color_pattern[3] = {
	{.r = 175, .g = 143, .b = 22},
	{.r = 171, .g = 114, .b = 21},
	{.r = 185, .g = 127, .b = 42},
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

Rgb hop_color_pattern[5] = {
	{.r = 21, .g = 82, .b = 80},
	{.r = 17, .g = 86, .b = 91},
	{.r = 14, .g = 80, .b = 85},
	{.r = 14, .g = 78, .b = 82},
	{.r = 30, .g = 88, .b = 94},
};

Rgb scarecrow_hat_dark_brown = {.r = 125, .g = 81, .b = 33};
Rgb hop_keeper = {.r = 0, .b = 50, .g = 0};
Rgb blue_color = {.r = 0, .b = 255, .g = 0};

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
	printf("No button\n");
	return 0;
}


int	check_orange_color(XImage *zone_to_check)
{
	int orange_counter = 0;
	int tolerance = 5;
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
		printf("%d ORANGE PIXELS\n", orange_counter);
		printf("ORANGE BUTTON IN ZONE\n");
		return 1;
	}
	else
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
			unsigned pixel = XGetPixel(zone_to_check, j, i);
			Rgb rgb = convert_pixel_to_rgb(zone_to_check, pixel);
			if (abs(rgb.r - orange_button.r) > tolerance
			|| abs(rgb.g - orange_button.g) > tolerance
			|| abs(rgb.b - orange_button.b) > tolerance)
			{
				printf("COULD NOT FIND ORANGE CONTEXT MENU COLOR\n");
				break;
			}
			else
			{
				orange_pixel_counter++;
				printf("+1 ORANGE VISIBLE\n");
			}
		}
	}
	if (orange_pixel_counter >=  zone_to_check->width)
	{
		printf("Orange button of context menu spotted\n");
		printf("Orange pixels spotted : %d\n", orange_pixel_counter);
		return orange_pixel_counter;
	}
	printf("Orange pixels spotted : %d, less than width : %d\n", orange_pixel_counter, zone_to_check->width);
	return orange_pixel_counter;
}

int	ready_button_visible(WinManager *wm)
{
	Rectangle ready_button_zone = create_rectangle(1520, 790, 100, 30);
	XImage *ready_button_image = get_zone_to_check(wm, ready_button_zone);
	printf("checking if in combat ...\n");
	if (check_orange_context_menu_color(ready_button_image, orange_button, 3) > 100)
	{
		printf("Ready button found\n");
		return 1;
	}
	printf("COULD NOT SEE READY BUTTON, ASSUME YOU ARE NOT IN COMBAT MODE\n");
	return 0;
}

Rgb*	 get_color_sequence(WinManager *wm, Rectangle zone_r)
{
	Rgb *wheat_color_sequence;
	XImage *wheat_zone = get_zone_to_check(wm, zone_r);
	wheat_color_sequence = get_color_in_frame(wm, wheat_zone);

	sleep(4);
	XSync(wm->display, False);
	printf("---------------------\n");

	return wheat_color_sequence;
}

int	is_wheat(WinManager *wm, Rgb wheat, XImage *zone, Rectangle r_zone)
{
	int wheat_match_counter = 0;
	int tolerance = 10;
	int wheat_pixel_x = 0;
	int wheat_pixel_y = 0;
	for (int i = 0; i < zone->height; i++)
		for (int j = 0; j < zone->width; j++)
		{
			unsigned long pixel = XGetPixel(zone, j, i);
			Rgb pixel_color = convert_pixel_to_rgb(zone, pixel);
			printf("(%d, %d:", r_zone.x + j, r_zone.y + i);
			if (abs(wheat.r - pixel_color.r) < tolerance &&
			abs(wheat.r - pixel_color.r) < tolerance &&
			abs(wheat.r - pixel_color.r) < tolerance)
			{
				wheat_match_counter++;
				wheat_pixel_x = r_zone.x + j;
				wheat_pixel_y = r_zone.y + i;
				printf("pixel color match with wheat color\n");
			}
		}
	if (wheat_match_counter > 40)
	{
		printf("IT LOOKS LIKE WE FOUND WHEAT at (%d, %d)\n", r_zone.x, r_zone.y);
		reap_wheat(wm, wheat_pixel_x, wheat_pixel_y-50);
	}
	else
		printf("NO WHEAT FOUND IN ZONE\n");
	sleep(2);
		printf("WHEAT COUNTER : %d\n", wheat_match_counter);
		return 1;
}

void	build_color_matrix(Rgb color_matrix[1080][1920], XImage *pixel_zone, Rectangle zone)
{
	for (int y = 0; y < 1080; y++)
		for (int x = 0; x < 1920; x++)
			color_matrix[y][x] = (Rgb){0,0,0};

	for (int y = 0; y < pixel_zone->height; y++)
	{
		for (int x = 0; x < pixel_zone->width; x++)
		{
			unsigned long pixel = XGetPixel(pixel_zone, x, y);
			Rgb pixel_color = convert_pixel_to_rgb(pixel_zone, pixel);
			color_matrix[y][x] = pixel_color;
		}
	}
}

int	 compare_color_pattern(WinManager *wm, Rgb *ref_color_pattern, Rgb color_matrix[1080][1920], int pixel_pattern_length, int tolerance)
{
	int same_pattern_count = 0;
	bool match_found = false;
	for (int y = 0; y < 1080; y++)
	{
		for (int x = 0; x < 1920 - pixel_pattern_length; x++)
		{
			match_found = true;
			for (int i = 0; i < pixel_pattern_length; i++)
			{
				Rgb pixel = color_matrix[y][x + i];
				Rgb ref = ref_color_pattern[i];
				if (abs(pixel.r - ref.r) > tolerance ||
				abs(pixel.g - ref.g) > tolerance ||
				abs(pixel.b - ref.b) > tolerance)
				{
					match_found = false;
					break;
				}
			}
			if (match_found)
			{
				same_pattern_count++;
				printf("(%d, %d): PIXEL MATCH\n", x, y);
				reap_wheat(wm, x, y);
				if (ready_button_visible(wm) == 1)
					return 1;
			}
		}
	
	}
	printf("FOUND %d cereal matching pattern across the map\n", same_pattern_count);
	for (int i = 0; i < 2; i++)
		if (same_pattern_count < 1)
		{
			if (i == 1)
			{
				printf("could not found cereals twice, need to change map\n");
				return 0;
			}
			printf("didnt find matching cereals pattern, waiting 60sec\n");
			sleep(60);
		}
	return same_pattern_count;
}

Point	find_player(Rgb *ref_color_pattern, Rgb color_matrix[1080][1920], int pixel_pattern_length, int tolerance)
{
	Point player_pos;
	int same_pattern_counter = 0;
	bool match = false;
	for (int y = 0; y  < 790; y++)
	{
		for (int x = 0; x < 1920 - pixel_pattern_length; x++)
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
				player_pos.x = x;
				player_pos.y = y;
			}
		}
	}
	printf("FOUND A TOTAL OF %d PIXELS MATCHING PLAYER'S COLOR PATTERN ACROSS THE MAP\n", same_pattern_counter);
	if (same_pattern_counter < 1)
	{
		printf("COULD NOT FIND ANY PLAYER'S COLOR PATTERN\n");
		return (Point){-1, -1};
	}
	printf("PLAYER POS: [%d, %d]\n", player_pos.x, player_pos.y);
	return player_pos;
}

// this function will give accurate results only once the fight has started.
Point	find_enemy(Rgb color_matrix[1080][1920], Rgb enemy_color, int pixel_pattern_length, int tolerance)
{
	Point enemy_pos;
	int same_pattern_counter = 0;
	bool match = false;
	for (int y = 0; y  < 770; y++)
	{
		for (int x = 0; x < 1920 - pixel_pattern_length; x++)
		{
			match = true;
			for (int i = 0; i < pixel_pattern_length; i++)
			{
				Rgb pixel = color_matrix[y][x+i];
				if  (abs(pixel.r - enemy_color.r) > tolerance
				|| abs(pixel.g - enemy_color. g) > tolerance
				|| abs(pixel.b - enemy_color.b) > tolerance)
				{
					match = false;
					break;
				}
			}
			if (match)
			{
				same_pattern_counter++;
				enemy_pos.x = x;
				enemy_pos.y = y + 60;
			}
		}
	}
	printf("FOUND A TOTAL OF %d MATCHING ENEMY PATTERN ACROSS THE SCREEN\n", same_pattern_counter);
	if (same_pattern_counter < 1)
	{
		printf("COULD NOT FIND ANY ENEMY MATCHING PATTERN MATCH\n");
		return (Point){-1, -1};
	}
	printf("ENEMY POS: [%d, %d]\n", enemy_pos.x, enemy_pos.y);
	return enemy_pos;
}

// we have enemy pos and red square pos
// for each red square, we do the difference with the enemy pos -> diff = enemypos - red_square
// we will place on the smallest diff for that current redsquare

int	get_red_square_pos(Rgb color_matrix[1080][1920], int pixel_pattern_length, int tolerance, Point player_pos, Point enemy_pos, Point red_square[])
{
	// on regarde les pattern rouge de 88 pixels qui se suivent
	// une case rouge represente 88 pixels rouge a 255 0 0
	// donc si on veut se mettre au milieu on se met a 44 px.
	Rgb red_square_color_pattern[pixel_pattern_length];
	int red_square_counter = 0;
	bool match = false;
	Point red_square_pos;
	printf("PLAYER IS CURRENTLY IN (%d, %d)\n", player_pos.x, player_pos.y);
	printf("ENEMY IS CURRENTLY IN (%d, %d)\n", enemy_pos.x, enemy_pos.y);
	printf("X DISTANCE BETWEEN PLAYER AND ENEMY : %d\n", abs(player_pos.x - enemy_pos.x));
	printf("Y DISTANCE BETWEEN PLAYER AND ENEMY : %d\n", abs(player_pos.y - enemy_pos.y));
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
				printf("RED SQUARE POS: [%d, %d]\n", red_square_pos.x, red_square_pos.y);
			}
		}
	}
	printf("FOUND A TOTAL OF %d RED SQUARES ACROSS THE SCREEN\n", red_square_counter);
	if (red_square_counter < 1)
	{
		printf("COULD NOT FIND ANY RED SQUARE ON MAP\n");
		return 1;
	}
	printf("RED SQUARE POS: [%d, %d]\n", red_square_pos.x, red_square_pos.y);
	return red_square_counter;
}

// this function will return the smallest distance between player enemy
// it will go through each red square and do the difference with enemy x and y
// it takes a list of red square,its size and the enemy position
Point	find_closest_placement_to_enemy(Point red_square[], int size, Point enemy_pos)
{
	Point placement;
	int distances[size]; 
	int distance = 0;
	printf("ENEMY POS : (%d, %d)\n", enemy_pos.x, enemy_pos.y);
	int smallest_distance = 0;
	for (int i = 0; i < size; i++)
	{
		distances[i] = abs(red_square[i].x - enemy_pos.x);
		distances[i] += abs(red_square[i].y - enemy_pos.y);
		if (distances[i] < distances[0])
			{
				distances[0] = distances[i];
				smallest_distance = distances[0];
				placement.x = red_square[i].x;
				placement.y = red_square[i].y;
			}
	}
	printf("SMALLEST DISTANCE BETWEEN PLAYER AND ENEMY LOCATED IN : (%d, %d)\n", placement.x, placement.y);
	return placement;
}

// get current position of both player and enemy during the fight
// do the difference
// if enemy.x > player.x => move left
// until enemy.x - player.x < 150
// same for y
// move_towards_enemy() will call get enemy pos and get player pos during the fight
// at each call in will do the difference in the coordinates and move towards the enemy regarding x and y difference

void	move_towards_enemy()
{
	Rgb color_matrix[1080][1920];
	for (int y = 0; y  < 790; y++)
	{
		for (int x = 0; x < 1920 ; x++)
		{
			Rgb pixel = color_matrix[y][x];
		}
	}
	Point player_pos = find_player(mandrage_color_pattern, color_matrix, 10, 5);
}

void open_inventory(WinManager *wm)
{
	move_mouse(wm, 1322, 886);
	sleep(1);
	fake_click(wm, 1, true);
	sleep(1);
}

void close_inventory(WinManager *wm)
{
	move_mouse(wm, 1629, 122);
	sleep(1);
	fake_click(wm, 1, true);
	sleep(1);
}

int	check_orange_color_pods(WinManager *wm, XImage *zone_to_check)
{
	int orange_counter = 0;
	int tolerance = 5;
	open_inventory(wm);
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
	if (orange_counter > 5)
	{
		printf("FULL PODS\n");
		return 1;
	}
	else
	{
		printf("pas encore full pods\n");
		close_inventory(wm);
	}
	return 0;
}



/*
int	test_match(WinManager *wm, Rgb *ref_color_pattern, Point pixel_match[], int size)
{
	int context_menu_counter = 0;
	int context_menu_hover = 0; 
	Rgb color_matrix[1920][1080];
	for (int i = 0; i < size; i+=10)
	{
		move_mouse(wm, pixel_match[i].x, pixel_match[i].y);
		sleep(.3);
		fake_click(wm, 1, true);
		sleep(.3);
		context_menu_counter = compare_colors(ref_color_pattern, color_matrix, 3, pixel_match[size]);
		context_menu_counter += compare_colors(ref_color_pattern, color_matrix, 3, pixel_match[size]);
		if (context_menu_counter > 4)
			{
				move_mouse(wm, pixel_match[i].x + 50, pixel_match[i].y + 75);
				context_menu_hover = compare_colors(context_menu_orange, color_matrix[1920][1080], 3, pixel_match[size]);
				if (context_menu_hover > 2)
				{
					sleep(.5);
					fake_click(wm, 1, true);
					sleep(8);
				}
			}
	}
	return 0;
}
*/

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
	//zones ble 1 en 5, -24
	Rectangle r_a = create_rectangle(400, 166, 2, 3);
	Rgb *colors_zone_one;
	XImage *zone_one_frame_one = get_zone_to_check(wm, r_a);
	printf("COLORS IN FRAME 1 ZONE 1:\n");
	colors_zone_one = get_color_in_frame(wm, zone_one_frame_one);

	sleep(4);
	XSync(wm->display, False);
	printf("---------------------\n");

	/*
	Rectangle r_b = create_rectangle(1100, 600, 300, 400);
	Rgb *colors_zone_two;
	XImage *zone_two_frame_one = get_zone_to_check(wm, r_b);
	printf("COLORS IN FRAME 1 ZONE 2:\n");
	colors_zone_two = get_color_in_frame(wm, zone_two_frame_one);
	*/
	//compare_colors(zone_one_frame_one, zone_one_frame_two);
	// can return 0 1 2 3 according to the current frame we are
	return 0;
}

int	log_in(WinManager *wm)
{
	Rectangle orange_r = create_rectangle(1000, 650, 100, 20);
	XImage *orange_button_zone = get_zone_to_check(wm, orange_r);
	Rectangle log_r = create_rectangle(600, 500, 10, 10);
	XImage *log_zone = get_zone_to_check(wm, log_r);
	if (check_orange_color(orange_button_zone) == 1)
		click_orange_button(wm);
	else if (check_log_in(log_zone) == 1)
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
