#ifndef FARMER_H
#define FARMER_H

#include "mouse_manager.h"
#include "window_manager.h"

void	equip_faux(WinManager *wm);
void	open_inventory(WinManager *wm);
void	close_iventory(WinManager *wm);	
void	reap(WinManager *wm, int x, int y);
int	reap_wheat(WinManager *wm, Rgb color_matrix[1080][1920]);
int	reap_barley(WinManager *wm, Rgb color_matrix[1080][1920]);
int	reap_oat(WinManager *wm, Rgb color_matrix[1080][1920]);
int	reap_hop(WinManager *wm, Rgb color_matrix[1080][1920]);


#endif
