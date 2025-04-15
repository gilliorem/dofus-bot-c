#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdio.h>
#include <unistd.h>
#include <X11/extensions/XTest.h>
#include <stdbool.h>
#include "screen_reading.h"
#include "window_manager.h"
#include "types.h"

void	get_mouse_coordinates(WinManager *wm, Point point);
void	move_mouse(WinManager *wm, int x, int y);
void	fake_click(WinManager *wm, int button, Bool dowm);
void	double_click(WinManager *wm);
void	click_log_button(WinManager *wm);
void	click_orange_button(WinManager *wm);
void	start(WinManager *wm);
void	reap_wheat(WinManager *wm, int x, int y);

void	open_inventory(WinManager *wm);
void	close_iventory(WinManager *wm);

void	equip_weapon(WinManager *wm);
void	tactical_mode(WinManager *wm);
void	equip_faux(WinManager *wm);
void	place_player(WinManager *wm, Point placement);

void	move_right(WinManager *wm, Point player_pos);
void	move_left(WinManager *wm, Point player_pos);
void	move_up(WinManager *wm, Point player_pos);
void	move_down(WinManager *wm, Point player_pos);

void	move_down_left(WinManager *wm, Point player_pos);
void	move_up_right(WinManager *wm, Point player_pos);
void	move_up_left(WinManager *wm, Point player_pos);

void	move_towards_enemy(WinManager *wm, Rgb color_matrix[1080][1920]);

void	boost(WinManager *wm, Point player);
void	attack(WinManager *wm, Point enemy);

#endif
