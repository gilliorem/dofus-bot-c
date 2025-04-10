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

Rectangle	create_rectangle(int x, int y, unsigned int width, unsigned int height);
XImage	*get_zone_to_check(WinManager *wm, Rectangle rectangle);
int	get_bit_shift(unsigned long color_mask);
Rgb	convert_pixel_to_rgb(XImage *zone_to_check, unsigned long pixel);
Rgb*	get_color_in_frame(WinManager *wm, XImage *zone_to_check);
int	check_color(XImage *zone_to_check);
int	check_log_in(XImage *zone_to_check);
int	check_orange_color(XImage *zone_to_check);
Rgb*	get_color_sequence(WinManager *wm, Rectangle r_zone);
int	is_wheat(WinManager *wm, Rgb wheat, XImage *zone, Rectangle r_zone);
XImage	**get_nzone(WinManager *wm, int n);
void	build_color_matrix(Rgb color_matrix[1920][1080], XImage *pixel_zone, Rectangle zone);
int	compare_color_pattern(WinManager *wm, Rgb *ref_color_pattern, Rgb color_matrix[1920][1080], int pixel_pattern_length, Point pixel_match[]);
int	test_match(WinManager *wm, Rgb *ref_pattern, Point pixel_match[], int size);
int	compare_colors(XImage *zone_to_check_a, XImage *zone_to_check_b);
void	open_inventory(WinManager *wm);
void	close_inventory(WinManager *wm);
int	check_orange_color_pods(WinManager *wm, XImage *zone_to_check);
int	context_menu_visible(WinManager *wm, Point pixel_match[], int size);

int	check_frame(WinManager *wm);
int	log_in(WinManager *wm);

#endif
