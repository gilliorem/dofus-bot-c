#ifndef SCREEN_READING_H
#define SCREEN_READING_H

#include "event_handler.h"
#include <stdio.h>
#include "window_manager.h"
#include "types.h"

extern Rgb orange_button;
extern Rgb log_in_button;
extern Rgb wheat;
extern Rgb context_menu_light_gray[3];
extern Rgb context_menu_dark_gray[3];
extern Rgb context_menu_orange[3];
extern Rgb wheat_color_pattern[3];
extern Rgb barley_color_pattern[3];
extern Rgb oat_color_pattern[3];
extern Rgb hop_color_pattern[5];
extern Rgb mandrage_color_pattern[3];
extern Rgb hop_mob;
extern Rgb blue_color;
extern Rgb scarecrow_hat_dark_brown;

Rectangle	create_rectangle(int x, int y, unsigned int width, unsigned int height);
XImage	*get_zone_to_check(WinManager *wm, Rectangle rectangle);
int	get_bit_shift(unsigned long color_mask);
Rgb	convert_pixel_to_rgb(XImage *zone_to_check, unsigned long pixel);
Rgb*	get_color_in_frame(WinManager *wm, XImage *zone_to_check);
int	check_log_in(XImage *zone_to_check);
int	check_orange_color(XImage *zone_to_check);
Rgb*	get_color_sequence(WinManager *wm, Rectangle r_zone);
int	log_in(WinManager *wm);
int	check_orange_context_menu_color(XImage *zone_to_check, Rgb orange_button, int tolerance);
int	ready_button_visible(WinManager *wm);
void	build_color_matrix(Rgb color_matrix[1080][1920], XImage *pixel_zone, Rectangle zone);
bool	pattern_match(Rgb color_matrix[1080][1920], Rgb *ref_color_pattern, int pattern_length, int x, int y, int tolerance);
int	find_matching_pattern(Rgb *ref_color_pattern, Rgb color_matrix[1080][1920], int pattern_length, int tolerance, Point matches[216]);
void	print_matching_pattern_position(int size, Point matches[size]);
int	check_orange_color_pods(WinManager *wm);
int	context_menu_visible(WinManager *wm, Point pixel_match[], int size);
Point	find_player(Rgb *ref_color_pattern, Rgb color_matrix[1080][1920], int pixel_pattern_length, int tolerance);
Point	find_enemy(Rgb color_matrix[1080][1920],Rgb enemy_color, int pixel_pattern_length, int tolerance);
int	get_red_square_pos(Rgb color_matrix[1080][1920], int pixel_pattern_length, int tolerance, Point player_pos, Point enemy_pos, Point red_square[]);
Point	find_closest_placement_to_enemy(Point red_square[], int size, Point enemy_pos);


#endif
