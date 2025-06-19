#include "mouse_manager.h"
#include <math.h>
#include <stdlib.h>
#include "types.h"
#include "combat.h"
#include "screen_reading.h"
#include <unistd.h>

//ajouter un check pour voir si l'arme est deja equipee
// weapon etant dans ce cas l'arme de cac (ici, marteau bouftou)

int	check_hammer_zone(WinManager *wm)
{
	static Rgb hammer_matrix[100][100];
	printf("check hammer zone() Rgb zone created\n");
	build_color_matrix_small(wm, hammer_matrix, 1180, 943);
	Point white_pixel_list[50];
	int white_pixel = find_matching_pattern_small(white_pattern, 943, 1180, hammer_matrix, 3, 5, white_pixel_list);
	printf("Scanning hammer zone...\n");
	for (int i = 0; i < white_pixel; i++)
	{
		move_mouse(wm, white_pixel_list[i].x, white_pixel_list[i].y);
		usleep(100000);
	}
	if (white_pixel < 1)
	{
		printf("WHITE LINE NOT FOUND.\nReturn 0.\n");
		return 0;
	}
	return 1;
}

enum Weapon	check_weapon(WinManager *wm)
{
	// hammer pos: 1220 970
	// scythe pos: 1270 970
	// 	if the white line is 
	Rgb ref = {.r = 255, .g = 255, .b = 255};
	int tolerance = 5;
	Rectangle scythe_zone = create_rectangle(1274, 968, 1, 1);
	XImage *scythe_image = get_zone_to_check(wm, scythe_zone);
	unsigned long pixel = XGetPixel(scythe_image, 0, 0);
	Rgb scythe_color = convert_pixel_to_rgb(scythe_image, pixel);
	Rectangle weapon_zone = create_rectangle(1321, 968, 1, 1);
	XImage *weapon_image = get_zone_to_check(wm, weapon_zone);
	unsigned long w_pixel = XGetPixel(weapon_image, 0, 0);
	Rgb weapon_color = convert_pixel_to_rgb(weapon_image, w_pixel);
	if (abs(ref.r - weapon_color.r) < tolerance)
	{
		printf("Hammer equip\n");
		return WEAPON_HAMMER;
	}
	else if (abs(ref.r - scythe_color.r) < tolerance)
	{
		printf("Faux is equip\n");
		return WEAPON_SCYTHE;
	}
	printf("checking-weapon-state is incorrect \n");
	return 0;
}

void	equip_weapon(WinManager *wm)
{
	if (check_weapon(wm) != WEAPON_HAMMER)
	{
		printf("switching to weapon\n");
		double_click(wm, 1320, 968);
	}
}

// in order to check if still in combat mode can check the pixel in 1080, 1025 (white flag)
// check foireux car l'icone bouge : faire un check sur un autre element static, ou implementer un check dynamique 
// qui cherche l'icon et qui check son etat (couleur);

int	check_tactical_mode(WinManager *wm)
{
	Rgb ref = {.r = 0, .g = 153, .b = 0};
	int tolerance = 5;
	Rectangle tactical_zone = create_rectangle(1533, 754, 1, 1);
	XImage *tactical_image = get_zone_to_check(wm, tactical_zone);
	unsigned long pixel = XGetPixel(tactical_image, 0, 0);
	Rgb tactical_color = convert_pixel_to_rgb(tactical_image, pixel);
	printf("%d %d %d\n", tactical_color.r, tactical_color.g, tactical_color.b);
	if (abs(ref.r - tactical_color.r) < tolerance)
	{
		printf("Tactical mode ON.\n");
		return 1;
	}
	printf("Tactical mode OFF\n");
	return 0;
}

void	tactical_mode(WinManager *wm)
{
	if (check_tactical_mode(wm) == 1)
		return;
	move_mouse(wm, 1500, 760);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	place_player(WinManager *wm, Point placement)
{
	move_mouse(wm, placement.x, placement.y);
	sleep(.5);
	fake_click(wm, 1, True);
}

void	click_ready_button(WinManager *wm)
{
	click(wm, 1575, 807);
}

void placement(WinManager *wm, Rgb color_matrix[1080][1920])
{
	build_color_matrix(wm, color_matrix);
	Point red_square[50];
	Point player_pos = find_player(color_matrix, red_color_pattern, 35, 5);
	Point enemy_pos = find_enemy (color_matrix, blue_color_pattern, 35, 5);
	int red_squares = get_red_square_pos(color_matrix, 90, 3, player_pos, enemy_pos, red_square);
	if (red_squares < 1)
		return;
	player_pos = find_closest_placement_to_enemy(red_square, red_squares, enemy_pos);
	place_player(wm, player_pos);
	click_ready_button(wm);
	sleep(2);
}

void	move(WinManager *wm, int x, int y)
{
	move_mouse(wm, x, y); 
	usleep(100000);
	fake_click(wm, 1, True);
	usleep(50000);
	XSync(wm->display, False);
}

int	get_in_range_tile(WinManager *wm, Point grey_tile[], int grey_tiles, Point player, Point in_range_tile[])
{
	int counter = 0;
	for (int i = 0; i < grey_tiles; i++)
	{
		if (abs(player.x - grey_tile[i]. x) < (250/2) && abs(player.y - grey_tile[i].y) < (150 / 2))
		{
			in_range_tile[counter].x = grey_tile[i].x;
			in_range_tile[counter].y = grey_tile[i].y;
			printf("tile in range %d %d \n", grey_tile[i].x, grey_tile[i].y);
			counter++;
		}
	}
	printf("TILES IN RANGE : %d\n", counter);
	return counter;
}

/* valeurs de deplacement de 3PM +- 146x 74y 
 * -290 x
 * Rectangle de deplacement joueur : (pX, pY, 388, 153) 
 * case 1: dX 146 dY 74
 * case 2: dX -290 dY 74
 * case 3: dX 146 dY -74
 * case 4: dX -290 dY -74
 *  */

int	move_in_range(WinManager *wm, Rgb color_matrix[1080][1920], Point grey_tile[])
{
	int grey_tiles = get_dark_grey_tiles(color_matrix, 89, 3,  grey_tile);
	int tiles = 0;
	Point player = find_player(color_matrix, red_color_pattern, 34, 5);
	Point enemy = find_enemy(color_matrix, blue_color_pattern, 34, 5);
	if (enemy.x == 1920/2 && enemy.y == 1080/2)
		return 0;
	if (player.x == 1920/2 && player.y == 1080/2)
		return 0;
	int dx = 0, dy = 0; 
	int row = 0, col = 0;
	int tileX = 0, tileY = 0;
	int player_col = 0, player_row = 0;
	int enemy_col = 0, enemy_row = 0;
	int d_col = 0, d_row = 0;
	for (int i = 0; i < grey_tiles; i++)
	{
		tileX = grey_tile[i].x;
		tileY = grey_tile[i].y;
		printf("moving on every tiles\n");
		move_mouse(wm, tileX, tileY);
		sleep(1);
		dx = player.x - tileX;
		dy = player.y - tileY;
		col = tileX / 90;
		row = tileY / 45;
		/* verification pour avoir des tiles dans la map */
		if (abs(grey_tile[i].x)< 1801 && abs(grey_tile[i].x) > 0 && abs(grey_tile[i].y) < 800 && abs(grey_tile[i].y) > 0)
		{
			/* verification des tiles qui sont on portee 3 PM */
			if ((abs(dx) > 140 && abs(dx) < 155 && abs(dy) > 70 && abs(dy) < 80) || (abs(dx) > 285 && abs(dx) < 296 && abs(dy) > 70 && abs(dy) < 80))
			{
				build_color_matrix(wm, color_matrix);
				enemy = find_enemy(color_matrix, blue_color_pattern, 34, 5);
				player = find_player(color_matrix, red_color_pattern, 34, 5);
				player_col = player.x / 90;
				player_row = player.y / 45;
				enemy_col = enemy.x / 90;
				enemy_row = enemy.y / 45;
				d_col = player_col - enemy_col;
				d_row = player_row - enemy_row;

				/* have to fix this */
				if (abs(d_col) <= 1 && abs(d_row) <= 2)
				{
					printf("In Range for Attack !\n");
					boost(wm, color_matrix);
					attack(wm, color_matrix);
				}
				
				/* le player se trouve a gauche en haut de l'enemi */
				if (player.x < enemy.x && player.y < enemy.y && player.x < tileX && player.y < tileY)
				{
					move(wm, tileX, tileY);
					sleep(3);
					sword_fate(wm, color_matrix, tileX + 50, tileY + 25);
				}
				/* le player se trouve a droite en haut de l'enemi */
				if (player.x > enemy.x && player.y < enemy.y && player.x > tileX && player.y < tileY)
				{
					move(wm, tileX, tileY);
					sleep(3);
					sword_fate(wm, color_matrix, tileX - 50, tileY + 50);
				}
				/* le player se trouve a gauche en bas de l'enemi */
				if (player.x < enemy.x && player.y > enemy.y && player.x < tileX && player.y > tileY)
				{
					move(wm, tileX, tileY);
					sleep(3);
					sword_fate(wm, color_matrix, tileX + 50, tileY - 50);
				}
				/* le player se trouve a droite en bas de l'enemi */
				if (player.x > enemy.x && player.y > enemy.y && player.x > tileX && player.y > tileY)
				{
					move(wm, tileX, tileY);
					sleep(3);
					sword_fate(wm, color_matrix, tileX - 50, tileY - 50);
				}
				tiles++;
			}
			/* cas pour bouger a 2 PM */
			if ((abs(dx) > 45 && abs(dx) < 100 && abs(dy) > 30 && abs(dy) < 55) || (abs(dx) > 100 && abs(dx) < 180 && abs(dy) > 30 && abs(dy) < 50))
			{
				build_color_matrix(wm, color_matrix);
				enemy = find_enemy(color_matrix, blue_color_pattern, 34, 5);
				player = find_player(color_matrix, red_color_pattern, 34, 5);
				player_col = player.x / 90;
				player_row = player.y / 45;
				enemy_col = enemy.x / 90;
				enemy_row = enemy.y / 45;
				d_col = player_col - enemy_col;
				d_row = player_row - enemy_row;

				if (abs(d_col) <= 2 && abs(d_row) <= 1)
				{
					boost(wm, color_matrix);
					attack(wm, color_matrix);
				}
				
				/* le player se trouve a gauche en haut de l'enemi */
				if (player.x < enemy.x && player.y < enemy.y && player.x < tileX && player.y < tileY)
				{
					move(wm, tileX, tileY);
					sleep(3);
					sword_fate(wm, color_matrix, tileX + 50, tileY + 50);
				}
				/* le player se trouve a droite en haut de l'enemi */
				if (player.x > enemy.x && player.y < enemy.y && player.x > tileX && player.y < tileY)
				{
					move(wm, tileX, tileY);
					sleep(3);
					sword_fate(wm, color_matrix, tileX - 50, tileY + 50);
				}
				/* le player se trouve a gauche en bas de l'enemi */
				if (player.x < enemy.x && player.y > enemy.y && player.x < tileX && player.y > tileY)
				{
					move(wm, tileX, tileY);
					sleep(3);
					sword_fate(wm, color_matrix, tileX + 50, tileY - 50);
				}
				/* le player se trouve a droite en bas de l'enemi */
				if (player.x > enemy.x && player.y > enemy.y && player.x > tileX && player.y > tileY)
				{
					move(wm, tileX, tileY);
					sleep(3);
					sword_fate(wm,color_matrix,  tileX - 50, tileY - 50);
				}
				if (player.x == enemy.x)
				{
					move(wm, tileX, tileY);
				}
				if (player.y == enemy.y)
				{
					move(wm, tileX, tileY);
				}
				move(wm, tileX, tileY);
				move_mouse(wm, 700, 1000);
				tiles++;
				end_tour(wm);
			}
		}
	}
	return tiles;
}

int	move_in_tile(WinManager *wm, Rgb color_matrix[1080][1920], Point grey_tile[], int grey_tiles, Point in_range_tile[])
{
	Point player = find_player(color_matrix, red_color_pattern, 30, 2);
	Point enemy = find_enemy(color_matrix, blue_color_pattern, 30, 2);
	/* j'ai aussi besoin de re-calculer apres chaque mouvement du perso les in_range_tile */
	int tiles_in_range = get_in_range_tile(wm, grey_tile, grey_tiles, player, in_range_tile);
	printf("playerX : %d\n", player.x);
	printf("enemyX : %d\n", enemy.x);
	/* l'idee c'est de ne pas faire 2 fois la meme action : ne pas aller 2 fois
	 * pour ca j'incremente un counter a chaque action
	 * et le reset a l'action suivante 
	 * ne pas oublier que c'est une fonction qui etre appeler x fois jusqu'a ce que le
	 * joueur se retrouve avec un x et un y proche. 
	 * du coup je pense que je devrai partir sur le while ici 
	 * logic d'enum a utiliser quand on aura run ce code 
	*/
	int dx = player.x - enemy.x;
	int dy = player.y - enemy.y;
	printf("dx : %d\n", dx);
	printf("dy : %d\n", dy);
	while (1)
	{
		printf("je suis dans le while\n");
		build_color_matrix(wm, color_matrix);
		player = find_player(color_matrix, red_color_pattern, 34, 3);
		enemy = find_enemy(color_matrix, blue_color_pattern, 36, 3);
		dx = player.x - enemy.x;
		dy = player.y - enemy.y;
		printf("playerX : %d\n", player.x);
		printf("enemyX : %d\n", enemy.x);
		printf("dx : %d\n", dx);
		printf("dy : %d\n", dy);
		tiles_in_range = get_in_range_tile(wm, grey_tile, grey_tiles, player, in_range_tile);
		for (int i = 0; i < tiles_in_range; i++)	
		{
			/* pour l'instant on ne va pas se deplacer de maniere la plus optimisee (surement 1PM)
			 * mais c'est ok, on test.
			 * cas 1 : le joueur est 'a gauche' de l'ennemi */
			if (player.x < enemy.x && in_range_tile[i].x > player.x )
			{
				move(wm, in_range_tile[i].x, in_range_tile[i].y);
				end_tour(wm);
				break;
			}
			/* cas 2 : le joueur est 'a droite' de l'ennemi */
			if (player.x > enemy.x && in_range_tile[i].x < player.x )
			{
				move(wm, in_range_tile[i].x, in_range_tile[i].y);
				end_tour(wm);
				break;

			}
			/* cas 3 : le joueur est 'au dessus' de l'ennemi */ 
			if (player.y < enemy.y && in_range_tile[i].y > player.y) 
			{
				move(wm, in_range_tile[i].x, in_range_tile[i].y);
				end_tour(wm);
				break;
			}
			if (player.y > enemy.y && in_range_tile[i].y < player.y )
			{
				move(wm, in_range_tile[i].x, in_range_tile[i].y);
				end_tour(wm);
				break;
			}
		}
		if (abs(dx) < 50 && abs(dy) < 35)
			break;
	}
	return 0;
}



/*  convertit un Point pixel → (row,col) grille */
static inline void pixel_to_grid(Point p, int *row, int *col)
{
    *col = (p.x - 315) / 97;    /* X → colonne */
    *row = (p.y -  63) / 48;    /* Y → ligne   */
}

void	find_player_range_tiles(WinManager *wm, Rgb matrix[1080][1920])
{
    /* -------- 1. détection joueur / ennemi ------------------ */
    Point player = find_player(matrix, red_color_pattern , 34, 5);
    Point enemy  = find_enemy (matrix, blue_color_pattern, 34, 5);

    int p_row, p_col, e_row, e_col;
    pixel_to_grid(player, &p_row, &p_col);
    pixel_to_grid(enemy , &e_row, &e_col);

    /* déjà à portée ? */
    if (abs(p_col - e_col) <= 2 && abs(p_row - e_row) <= 1) {
        boost(wm, matrix); 
	attack(wm, matrix);
	return;
    }

    /* -------- 2. fenêtre tronquée autour du joueur ---------- */
    Rectangle zone = build_po_zone(player);      /* 388×161 max */

    /* -------- 3. collecte des tuiles gris clair/foncé ------- */
    Point tiles[25];
    int n = 0;
    n += find_matching_pattern_in_rect(light_grey_pattern, 89, 3,
                                       matrix, zone, tiles + n, 25 - n);
    n += find_matching_pattern_in_rect(dark_grey_pattern , 89, 3,
                                       matrix, zone, tiles + n, 25 - n);

    if (n == 0) return;          /* aucune tuile jouable */

    /* -------- 4. choix de la meilleure tuile ---------------- */
    int want_up    = (p_row > e_row);
    int want_down  = (p_row < e_row);
    int want_left  = (p_col > e_col);
    int want_right = (p_col < e_col);

    int best = -1, best_dist = 9999;

    for (int pass = 0; pass < 2; ++pass)          /* pass 0 = quadrant, 1 = fallback */
    {
        for (int i = 0; i < n; ++i)
        {
            int t_row, t_col; pixel_to_grid(tiles[i], &t_row, &t_col);

            if (pass == 0) {                      /* filtre quadrant */
                if (want_up    && t_row >= e_row) continue;
                if (want_down  && t_row <= e_row) continue;
                if (want_left  && t_col >= e_col) continue;
                if (want_right && t_col <= e_col) continue;
            }

            int dist = abs(t_col - e_col) + abs(t_row - e_row);
            if (dist < best_dist) { best_dist = dist; best = i; }
        }
        if (best != -1) break;                    /* trouvé dans le quadrant */
    }

    if (best == -1) return;                       /* toujours rien → on ne bouge pas */

    /* -------- 5. déplacement + tentative d’attaque ---------- */
    move(wm, tiles[best].x, tiles[best].y);
    sleep(2);                                     /* animation */

    build_color_matrix(wm, matrix);               /* re-scan */
    player = find_player(matrix, red_color_pattern, 34, 5);
    pixel_to_grid(player, &p_row, &p_col);

    if (abs(p_col - e_col) <= 2 && abs(p_row - e_row) <= 1) {
        boost(wm, matrix); 
	attack(wm, matrix);
    }
}


void	boost(WinManager *wm, Rgb color_matrix[1080][1920])
{
	build_color_matrix(wm, color_matrix);
	Point player = find_player(color_matrix, red_color_pattern, 34, 5);
	int x = 1285;
	for(int i = 0; i < 3; i++)
	{
		click(wm, x, 975);
		click(wm, player.x, player.y);
		x+= 50;
	}
}

void	attack(WinManager *wm, Rgb color_matrix[1080][1920])
{
	int i = 0;
	while ((check_enemy_life(wm, color_matrix) != 0 && end_of_fight(wm) != 1 && is_my_turn(wm) == 1) || i > 2)
	{
		build_color_matrix(wm, color_matrix);
		Point enemy = find_enemy(color_matrix, blue_color_pattern, 34, 5);
		for (int i = 0; i < 2; i++)
		{
			if (check_enemy_life(wm, color_matrix) != 0)
			{
				click(wm, 1440, 975);
				click(wm, enemy.x, enemy.y);
				sleep(1);
			}
			else if (is_my_turn(wm) != 1)
				sleep(4);
		}
		end_tour(wm);
		i++;
	}
}

void	sword_fate(WinManager *wm, Rgb color_matrix[1080][1920], int x, int y)
{
	if (check_enemy_life(wm, color_matrix) != 0)
	{
		click(wm, 1540, 975);
		click(wm, x+50, y+25);
		sleep(1);
	}
	end_tour(wm);
}

void	end_tour(WinManager *wm)
{
	click(wm, 1200, 1040);
	sleep(2);
}

void	close_fight_window(WinManager *wm)
{
	click(wm, 1326, 723);
	sleep(1);
}
