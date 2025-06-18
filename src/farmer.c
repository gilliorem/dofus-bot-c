#include "mouse_manager.h"
#include "screen_reading.h"
#include <stdlib.h>
#include "farmer.h"
#include "combat.h"
#include <unistd.h>

void	equip_scythe(WinManager *wm)
{
	move_mouse(wm, 1285, 975);
	sleep(1);
	double_click(wm, 1285, 975);
	sleep(2);
	XSync(wm->display, False);
}

int open_inventory(WinManager *wm)
{
	move_mouse(wm, 1314, 884);
	sleep(1);
	fake_click(wm, 1, true);
	sleep(1);
	return 0;
}

void close_inventory(WinManager *wm)
{
	move_mouse(wm, 1629, 122);
	sleep(1);
	fake_click(wm, 1, true);
	sleep(1);
}

void	reap(WinManager* wm, int x, int y)
{	
	move_mouse(wm, x, y);
	sleep(1);
	fake_click(wm, 1, True);
	sleep(1);
	move_mouse(wm, x+=40, y+=50);
	sleep(1);
	fake_click(wm, 1, True);
	sleep(12);
}

void	reap_f(WinManager *wm, int x, int y)
{
	move_mouse(wm, x, y);
	sleep(1);
	fake_click(wm, 1, True);
	sleep(1);
	move_mouse(wm, x+=40, y+=100);
	sleep(1);
	fake_click(wm, 1, True);
	sleep(8);
}

int	reap_wheat(WinManager *wm, Rgb color_matrix_v[1920][1080])
{
	Point wheat_position[50];
	int wheats = find_matching_pattern_v(wheat_color_pattern_vertical,color_matrix_v, 6, wheat_position);
	printf("scanning the map for wheat...\n");
	for (int i = 0; i < wheats; i++)
	{
		move_mouse(wm, wheat_position[i].x, wheat_position[i].y);
		usleep(100000);
	}
	if (wheats < 1)
	{
		printf("No wheat found, abort\n");
		return 0;
	}
	if (ready_button_visible(wm) == 1)
		return 1;
	for (int i = 0; i < wheats; i++)
	{
		printf("Found wheat in (%d %d)\n", wheat_position[i].x, wheat_position[i].y);
		reap(wm, wheat_position[i].x, wheat_position[i].y);
		if (ready_button_visible(wm) == 1)
		{
			printf("Ready button found.\n");
			return 1;
		}
	}
	open_inventory(wm);
	if (full_pods(wm) == 1)
	{
		printf("Inventory is full, need to go drop resource at the bank.\n");
		close_inventory(wm);
		return 2;
	}
	close_inventory(wm);
	return 0;
}

int	reap_barley(WinManager *wm, Rgb color_matrix[1080][1920])
{
	Point barley[216];
	if (check_weapon(wm) != WEAPON_SCYTHE)
		equip_scythe(wm);
	int barleys = find_matching_pattern(barley_color_pattern, color_matrix, 3, 8, barley);
	if (barleys < 1)
		return 0;
	for (int i = 1; i < barleys; i++)
	{
		printf("Found barley in (%d %d)\n", barley[i].x, barley[i].y);
		reap(wm, barley[i].x, barley[i].y);
		if (ready_button_visible(wm) == 1)
		{
			printf("Ready button found, Fight has started\n");
			return 1;
		}
	}
	open_inventory(wm);
	if (full_pods(wm) == 1)
	{
		printf("Inventory is full, need to go drop resource at the bank.\n");
		close_inventory(wm);
		return 2;
	}
	close_inventory(wm);
	return 0;
}

int	reap_oat(WinManager *wm, Rgb color_matrix[1080][1920])
{
	Point oat[216];
	if (check_weapon(wm) != WEAPON_SCYTHE)
		equip_scythe(wm);
	int oats = find_matching_pattern(oat_color_pattern, color_matrix, 3, 15, oat);
	if (oats < 1)
		return 0;
	for (int i = 1; i < oats; i++)
	{
		printf("Found oat in (%d %d)\n", oat[i].x, oat[i].y);
		reap(wm, oat[i].x, oat[i].y);
		if (ready_button_visible(wm) == 1)
			return 1;
	}
	open_inventory(wm);
	if (full_pods(wm) == 1)
	{
		close_inventory(wm);
		return 2;
	}
	close_inventory(wm);
	return 0;
}

int	reap_hop(WinManager *wm, Rgb color_matrix[1080][1920])
{
	for (int i = 0; i < 10; i++)
	{
		Point hop[216];
		if (ready_button_visible(wm) == 1)
			return 1;
		if (check_weapon(wm) != WEAPON_SCYTHE)
			equip_scythe(wm);
		int hops = find_matching_pattern(hop_color_pattern, color_matrix, 3, 2, hop);
		if (hops < 1)
		{
			printf("Hop not find\n");
			return 0;
		}
		for (int i = 1; i < hops; i++)
		{
			printf("Found hop in (%d %d)\n", hop[i].x, hop[i].y);
			reap(wm, hop[i].x, hop[i].y);
			if (ready_button_visible(wm) == 1)
				return 1;
			else if (ok_button_visible(wm) == 1)
				click(wm, 1230, 480);
		}
		open_inventory(wm);
		if (full_pods(wm) == 1)
		{
			close_inventory(wm);
			return 2;
		}
		close_inventory(wm);
	}
	return 0;
}

int	reap_flax(WinManager *wm, Rgb color_matrix[1080][1920])
{
	if (ready_button_visible(wm) == 1)
	{
		printf("found ready boutton\n");
		if (check_weapon(wm) != WEAPON_HAMMER)
			equip_weapon(wm);
		return 1;
	}
	Point player_pos = find_player(color_matrix, red_color_pattern, 34, 5);
	if (player_pos.x != 1920/2)
		return 1;
	ok_button_visible(wm);
	Point flax[216];
	int flaxs = find_matching_pattern(flax_color_pattern, color_matrix, 3, 8, flax);
	if (flaxs < 1)
	{
		printf("FARMER.C no flax found, return 0\n");
		return 0;
	}
	for (int i = 0; i < 10; i++)
	{
		build_color_matrix(wm, color_matrix);
		if (ready_button_visible(wm) == 1)
		{
			printf("found ready boutton\n");
			if (check_weapon(wm) != WEAPON_HAMMER)
				equip_weapon(wm);
			return 1;
		}
		if (ok_button_visible(wm) == 1)
			click(wm, 1000, 500);
		if (check_weapon(wm) != WEAPON_SCYTHE)
			equip_scythe(wm);
		flaxs = find_matching_pattern(flax_color_pattern, color_matrix, 3, 8, flax);
		printf("Found %d flax\n", flaxs);
		if (i > 2 && flaxs < 3)
		{
			printf("2 SCANS LESS THAN 3 FLAXS. RETURN 0\n");
			return 0;
		}
		if (flaxs < 1)
		{
			printf("Flax not find\n");
			return 0;
		}
		for (int i = 1; i < flaxs; i++)
		{
			click(wm, 1639, 1028);
			printf("Found flax in (%d %d)\n", flax[i].x, flax[i].y);
			reap_f(wm, flax[i].x, flax[i].y);
			if (ready_button_visible(wm) == 1)
				return 1;
			if (ok_button_visible(wm) == 1)
				click(wm, 1000, 500);
		}
		open_inventory(wm);
		if (full_pods(wm) == 1)
		{
			close_inventory(wm);
			return 2;
		}
		close_inventory(wm);
	}
	return 0;
}

