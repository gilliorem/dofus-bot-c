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

#endif
