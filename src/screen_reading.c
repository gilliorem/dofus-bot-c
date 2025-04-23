#include "types.h"
#include <stdlib.h>
#include <unistd.h>
#include "screen_reading.h"
#include "mouse_manager.h"
#include "window_manager.h"

Rgb orange_button = {.r = 255, .g = 102, .b = 0};
Rgb ok_orange_button = {.r = 255, .g = 97, .b = 0};
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

Rgb wheat_color_pattern[4] = {
	{.r = 169, .g = 122, .b = 24},
	{.r = 161, .g = 101, .b = 4},
	{.r = 168, .g = 107, .b = 9},
	{.r = 176, .g = 125, .b = 18}
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
				printf("(%d, %d): %d, %d, %d %ld\n",
						(j), (i), rgb.r, rgb.g, rgb.b, pixel);
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

int	ok_button_visible(WinManager *wm)
{
	Rectangle ok_button_zone = create_rectangle(900, 477, 200, 50);
	XImage *ok_button_image = get_zone_to_check(wm, ok_button_zone);
	if (check_orange_context_menu_color(ok_button_image, ok_orange_button, 3) > 100)
	{
		printf("OK BUTTON found\n");
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

Rgb*	 get_color_sequence(WinManager *wm, Rectangle zone_r)
{
	Rgb *color_sequence;
	XImage *image_zone = get_zone_to_check(wm, zone_r);
	color_sequence = get_color_in_frame(wm, image_zone);
	sleep(4);
	XSync(wm->display, False);
	printf("---------------------\n");
	return color_sequence;
}

void	build_color_matrix(WinManager *wm, Rgb color_matrix[1080][1920])
{
	Rectangle screen_zone = create_rectangle(0, 0, 1920, 1080);
	XImage *screen_image = get_zone_to_check(wm, screen_zone);
	for (int y = 0; y < 1080; y++)
		for (int x = 0; x < 1920; x++)
			color_matrix[y][x] = (Rgb){0,0,0};

	for (int y = 0; y < screen_image->height; y++)
	{
		for (int x = 0; x < screen_image->width; x++)
		{
			unsigned long pixel = XGetPixel(screen_image, x, y);
			Rgb pixel_color = convert_pixel_to_rgb(screen_image, pixel);
			color_matrix[y][x] = pixel_color;
		}
	}
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

int	find_matching_pattern(Rgb *ref_color_pattern, Rgb color_matrix[1080][1920], int pattern_length, int tolerance, Point matches[216])
{
	int	match_counter = 0;
	for (int y = 0; y < 1080; y++)
	{
		for (int x = 0; x < 1920 - pattern_length; x++)
		{
			if (pattern_match(color_matrix, ref_color_pattern, pattern_length, x, y, tolerance))
			{
				match_counter++;
				matches[match_counter].x = x;
				matches[match_counter].y = y;
			}
		}
	}
	return match_counter;
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

int	get_red_square_pos(Rgb color_matrix[1080][1920], int pixel_pattern_length, int tolerance, Point player_pos, Point enemy_pos, Point red_square[])
{
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

int	check_enemy_life(WinManager *wm)
{
	int tolerance = 3;
	Rectangle life_zone = create_rectangle(1556, 836, 7, 1);
	XImage* life_zone_image = get_zone_to_check(wm, life_zone);
	for (int i = 0; i < life_zone.width; i++)
	{
		unsigned long pixel = XGetPixel(life_zone_image, i, life_zone.height);
		Rgb rgb = convert_pixel_to_rgb(life_zone_image, pixel);
		if (abs(rgb.b - blue_color.b) < tolerance)
		{
			printf("Enemy is dead\n");
			return 1;
		}
		else
		{
			printf("Enemy isnt dead yet\n");
			return 2;
		}
	}
	return 0;
}

