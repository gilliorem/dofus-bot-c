#ifndef LOG_H
#define LOG_H

#include "mouse_manager.h"
#include "window_manager.h"

int	start(WinManager *wm);
int	character_screen(WinManager *wm);
int	is_in_game(WinManager *wm);
int	log_in(WinManager *wm);

#endif
