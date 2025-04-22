#include "mouse_manager.h"
#include "screen_reading.h"

void	equip_faux(WinManager *wm)
{
	move_mouse(wm, 1285, 975);
	sleep(.5);
	double_click(wm);
	sleep(2);
	XSync(wm->display, False);
}

void open_inventory(WinManager *wm)
{
	move_mouse(wm, 1322, 886);
	sleep(1);
	fake_click(wm, 1, true);
	sleep(1);
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
	move_mouse(wm, x+=50, y+=70);
	sleep(1);
	fake_click(wm, 1, True);
	sleep(15);
}

int	reap_wheat(WinManager *wm, Rgb color_matrix[1080][1920])
{
	Point wheat[216];
	int wheats = find_matching_pattern(wheat_color_pattern, color_matrix, 4, 10, wheat);
	if (ready_button_visible(wm) == 1)
		return 1;
	for (int i = 1; i < wheats; i++)
	{
		printf("Found wheat in (%d %d)\n", wheat[i].x, wheat[i].y);
		reap(wm, wheat[i].x, wheat[i].y);
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

int	reap_barley(WinManager *wm, Rgb color_matrix[1080][1920])
{
	Point barley[216];
	int barleys = find_matching_pattern(barley_color_pattern, color_matrix, 3, 8, barley);
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
	int oats = find_matching_pattern(oat_color_pattern, color_matrix, 3, 15, oat);
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
	Point hop[216];
	int hops = find_matching_pattern(hop_color_pattern, color_matrix, 3, 12, hop);
	for (int i = 1; i < hops; i++)
	{
		printf("Found hop in (%d %d)\n", hop[i].x, hop[i].y);
		reap(wm, hop[i].x, hop[i].y);
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

