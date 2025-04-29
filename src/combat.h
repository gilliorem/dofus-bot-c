#ifndef COMBAT_H
#define COMBAT_H

#include "mouse_manager.h"
#include "window_manager.h"

enum Weapon {
	WEAPON_HAMMER,
	WEAPON_SCYTHE,
};

enum Weapon	check_weapon(WinManager *wm);
void	equip_weapon(WinManager *wm);
int	check_tactical_mode(WinManager *wm);
void	tactical_mode(WinManager *wm);
void	place_player(WinManager *wm, Point placement);
void	placement(WinManager *wm, Rgb color_matrix[1080][1920]);
void	click_ready_button(WinManager *wm);
void	move(WinManager *wm, int x, int y);
int	get_in_range_tile(WinManager *wm, Point grey_tile[], int grey_tiles, Point player, Point in_range_tile[]);
int	move_in_tile(WinManager *wm, Rgb color_matrix[1080][1920], Point grey_tile[], int tiles_in_range, Point in_range_tile[]);
int	move_towards_enemy_x(WinManager *wm, Rgb color_matrix[1080][1920]);
int	move_towards_enemy_y(WinManager *wn, Rgb color_matrix[1080][1920]);
void	boost(WinManager *wm, Rgb color_matrix[1080][1920]);
void	attack(WinManager *wm, Rgb color_matrix[1080][1920]);
void	end_tour(WinManager *wm);
void	close_fight_window(WinManager *wm);
int		move_in_range(WinManager *wm, Rgb color_matrix[1080][1920], Point grey_tile[], int grey_tiles);
#endif

