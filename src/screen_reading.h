#ifndef SCREEN_READING_H
#define SCREEN_READING_H

#include "mouse_manager.h"
#include "window_manager.h"
#include "types.h"
#include <stdio.h>

extern Rgb orange_button;
extern Rgb ready_button;
extern Rgb ok_orange_button;
extern Rgb log_in_button;
extern Rgb wheat;
extern Rgb context_menu_light_gray[3];
extern Rgb context_menu_dark_gray[3];
extern Rgb context_menu_orange[3];
extern Rgb wheat_color_pattern[4];
extern Rgb wheat_color_pattern_vertical[8];
extern Rgb barley_color_pattern[3];
extern Rgb oat_color_pattern[3];
extern Rgb hop_color_pattern[3];
extern Rgb hop_color_pattern_v[6];
extern Rgb white_pattern[6];
extern Rgb flax_color_pattern[3];
extern Rgb flax_color_pattern_v[6];
extern Rgb mandrage_color_pattern[3];
extern Rgb hop_mob;
extern Rgb blue_color;
extern Rgb red_color_pattern[36];
extern Rgb blue_color_pattern[36];
extern Rgb scarecrow_hat_dark_brown;
extern Rgb light_grey; 
extern Rgb dark_grey; 
extern Rgb light_grey_pattern[89]; 
extern Rgb dark_grey_pattern[89];

void	update_screen_matrix(WinManager *wm);
Rgb	(*get_screen_matrix(void))[1920];

void	update_screen_matrix_v(WinManager *wm);
Rgb	(*get_screen_matrix_v(void))[1080];

void get_grey_tile_pattern(Rgb grey_tile_color, Rgb grey_pattern[89]);
Rgb* red_circle_pattern(int len);
Rectangle	create_rectangle(int x, int y, unsigned int width, unsigned int height);
XImage	*get_zone_to_check(WinManager *wm, Rectangle rectangle);
int	get_bit_shift(unsigned long color_mask);
Rgb	convert_pixel_to_rgb(XImage *zone_to_check, unsigned long pixel);
int	print_color_in_frame(WinManager *wm, XImage *zone_to_check);
int	check_log_in(XImage *zone_to_check);
int	check_orange_color(XImage *zone_to_check);
void	print_color_sequence(WinManager *wm, Rectangle r_zone);
int compares_rgb_sequences(WinManager *wm, Rgb *ref_pattern, int pattern_len, Rectangle zone_r, int tolerance);
int	check_orange_context_menu_color(XImage *zone_to_check, Rgb orange_button, int tolerance);
int	check_in_game(WinManager *wm);
int	ready_button_visible(WinManager *wm);
int	ok_button_visible(WinManager *wm);
int	full_pods(WinManager *wm);
bool	color_difference(Rgb ref, Rgb color, Rgb difference, Rgb tolerance);

bool	rgb_difference(Rgb temp, Rgb ref, Rgb tol);
bool	rgb_match(WinManager *wm, Rgb small_matrix[100][100], Rgb ref, Rgb tol, int x, int y);
int	count_matches(WinManager *wm, Rgb ref, Rgb small_matrix[100][100], Rgb tol, Point match[], int y, int x);
int	check_state(WinManager *wm);

void	build_color_matrix(WinManager *wm, Rgb color_matrix[1080][1920]);
bool	pattern_match(Rgb color_matrix[1080][1920], Rgb *ref_color_pattern, int pattern_length, int x, int y, int tolerance);
int	find_matching_pattern(Rgb *ref_color_pattern, Rgb color_matrix[1080][1920], int pattern_length, int tolerance, Point matches[216]);

void	build_color_matrix_vertical(WinManager *wm, Rgb color_matrix_v[1920][1080]);
bool	pattern_match_vertical(Rgb color_matrix_v[1920][1080], Rgb *ref_color_pattern, int pattern_len, int y, int x);
int	find_matching_pattern_v(Rgb *ref_color_pattern, Rgb color_matrix_v[1920][1080], int pattern_len, Point matches[]);

void	build_color_matrix_small(WinManager *wm, Rgb color_matrix[100][100], int x, int y);
bool	small_pattern_match(WinManager *wm, Rgb small_matrix[100][100], Rgb *ref_pattern, int pattern_len, int x, int y);
int	find_matching_pattern_small(Rgb *ref_color_pattern, int height, int width, Rgb color_matrix[height][width], int pattern_length, int tolerance, Point matches[216]);

Rectangle build_po_zone(Point p);
int find_matching_pattern_in_rect(Rgb *ref, int pattern_len, int tol,
                                  Rgb matrix[1080][1920],
                                  Rectangle r, Point matches[], int max_match);

Point	find_player(Rgb color_matrix[1080][1920], Rgb *ref_color_pattern, int pixel_pattern_length, int tolerance);
Point	find_enemy(Rgb color_matrix[1080][1920], Rgb *ref_color_pattern, int pixel_pattern_length, int tolerance);
int	get_red_square_pos(Rgb color_matrix[1080][1920], int pixel_pattern_length, int tolerance, Point player_pos, Point enemy_pos, Point red_square[]);
int		get_grey_tiles(Rgb color_matrix[1080][1920], int pattern_len, int tolerance, Point grey_tile[]);
int		get_light_grey_tiles(Rgb color_matrix[1080][1920], int pattern_len, int tolerance, Point grey_tile[]);
int		get_dark_grey_tiles(Rgb color_matrix[1080][1920], int pattern_len, int tolerance, Point grey_tile[]);
Point	find_closest_placement_to_enemy(Point red_square[], int size, Point enemy_pos);
int	check_movement_point(WinManager *wm, int tolerance);
int	is_my_turn(WinManager *wm);
int	check_enemy_life(WinManager *wm, Rgb color_matrix[1080][1920]);
int	end_of_fight(WinManager *wm);

#endif
