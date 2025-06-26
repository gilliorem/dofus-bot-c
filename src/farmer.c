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
	Rectangle inventory_zone = create_rectangle(1160, 855, 178, 68);
	XImage *inventory_image = get_zone_to_check(wm, inventory_zone);
	Rgb inventory_color = {51, 51, 51};
	
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

int	reap_wheat(WinManager *wm)
{
	static Rgb color_matrix_v[1920][1080];
	build_color_matrix_vertical(wm, color_matrix_v);
	Point wheat_position[50];
	int wheats = find_matching_pattern_v(wheat_color_pattern_vertical,color_matrix_v, 3, wheat_position);
	printf("scanning the map for wheat...\n");
	for (int i = 0; i < wheats; i++)
	{
		move_mouse(wm, wheat_position[i].x, wheat_position[i].y);
		usleep(100000);
	}
	printf("reap_wheat()>>>return;");
	//return 0;
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

int	reap_hop(WinManager *wm)
{
	static Rgb color_matrix_v[1920][1080];
	build_color_matrix_vertical(wm, color_matrix_v);
	Point hop_list[50];
	int hops = find_matching_pattern_v(hop_color_pattern_v, color_matrix_v, 4, hop_list);
	if (hops < 1)
	{
		printf("Hop not find\n");
		return 0;
	}
	printf("Scannig map for hop...\n");
	for (int i = 0; i < hops; i++)
	{
		move_mouse(wm, hop_list[i].x, hop_list[i].y);
		usleep(100000);
	}
	printf("Found %d hops on current map.\n", hops);
	//printf("reap_hop()>>RETURN<<");
	//return 0;

	for (int i = 1; i < hops; i++)
	{
		printf("Found hop in (%d %d)\n", hop_list[i].x, hop_list[i].y);
		reap(wm, hop_list[i].x, hop_list[i].y);
		if (ready_button_visible(wm) == 1)
			return 1;
		else if (ok_button_visible(wm) == 1)
			click(wm, 1230, 480);
	}
	return 0;
}

int	reap_flax(WinManager *wm) 
{
	static Rgb color_matrix_v[1920][1080];
	build_color_matrix_vertical(wm, color_matrix_v);
	Point flax[50];
	int flaxs = find_matching_pattern_v(flax_color_pattern_v, color_matrix_v, 4, flax);
	printf("Scanning for flax...\n");
	for (int i = 0; i < flaxs; i++)
	{
		int x = flax[i].x;
		int y = flax[i].y;
		move_mouse(wm, x, y);
		usleep(100000);
	}
	if (flaxs < 1)
	{
		printf("reap_flax(): DID NOT FIND FLAX. RETURNING 0.\n");
		return 0;
	}
	printf("Found %d flaxs on current map.\n", flaxs);
	//printf("reap_flax(): RETURN\n");
	//return 0;
	for (int i = 0; i < 10; i++)
	{
		build_color_matrix_vertical(wm, color_matrix_v);
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
		flaxs = find_matching_pattern_v(flax_color_pattern_v, color_matrix_v, 6, flax);
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
	}
	return 0;
}

