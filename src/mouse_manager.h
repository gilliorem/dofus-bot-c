#ifndef MOUSE_MANAGER_H
#define MOUSE_MANAGER_H

#include "mouse_manager.h"
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
void	click(WinManager *wm, int x, int y);
void	double_click(WinManager *wm, int x, int y);

#endif
