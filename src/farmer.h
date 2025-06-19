#ifndef FARMER_H
#define FARMER_H

#include "mouse_manager.h"
#include "window_manager.h"

void	equip_scythe(WinManager *wm);
int	open_inventory(WinManager *wm);
void	close_iventory(WinManager *wm);	
void	reap(WinManager *wm, int x, int y);
//int	reap_wheat(WinManager *wm, Rgb color_matrix_v[1920][1080]);
int	reap_wheat(WinManager *wm);
int	reap_barley(WinManager *wm, Rgb color_matrix[1080][1920]);
int	reap_oat(WinManager *wm, Rgb color_matrix[1080][1920]);
int	reap_hop(WinManager *wm);
int	reap_flax(WinManager *wm);


#endif
