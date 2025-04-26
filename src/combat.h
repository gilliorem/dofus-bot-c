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
void	move_right(WinManager *wm, Point player_pos);
void	move_left(WinManager *wm, Point player_pos);
void	move_up(WinManager *wm, Point player_pos);
void	move_down(WinManager *wm, Point player_pos);
void	move_down_right(WinManager *wm, Point player_pos);
void	move_down_left(WinManager *wm, Point player_pos);
void	move_up_right(WinManager *wm, Point player_pos);
void	move_up_left(WinManager *wm, Point player_pos);
int	move_towards_enemy_x(WinManager *wm, Rgb color_matrix[1080][1920]);
int	move_towards_enemy_y(WinManager *wn, Rgb color_matrix[1080][1920]);
void	boost(WinManager *wm, Rgb color_matrix[1080][1920]);
void	attack(WinManager *wm, Rgb color_matrix[1080][1920]);
void	end_tour(WinManager *wm);
void	close_fight_window(WinManager *wm);

#endif

