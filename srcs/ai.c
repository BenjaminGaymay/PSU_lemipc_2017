/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** ia
*/

#include "lemipc.h"

t_pos move_to(t_player *p)
{
	t_pos pos;

	pos.x = p->pos.x;
	pos.y = p->pos.y;
	if (p->pos.x < p->target.x)
		pos.x++;
	else if (p->pos.x > p->target.x)
		pos.x--;
	if (p->pos.y < p->target.y && pos.x == p->pos.x)
		pos.y++;
	else if (p->pos.y > p->target.y && pos.x == p->pos.x)
		pos.y--;

	return (pos);
}

size_t manhattan_dist(t_pos *p1, t_pos *p2)
{
	return abs(p1->x + p2->x) - abs(p1->y + p2->y);
}

t_pos look_ennemy(const char *map, t_player *p)
{
	t_pos pos;
	t_pos ennemy = {-1, -1};
	int min = -1;
	int dist;

	for (size_t i = 0; map[i] ; i++) {
		if (map[i] != ' '  && map[i] != '\n' && (size_t)(map[i] - 48) != p->team) {
			pos.x = i % (MAP_SIZE + 1);
			pos.y = i / (MAP_SIZE + 1);
			dist = manhattan_dist(&pos, &p->pos);
			if (dist < min || min == -1) {
				min = dist;
				memcpy(&ennemy, &pos, sizeof(pos));
			}
		}
	}
	return ennemy;
}

static bool within_map(const t_pos pos, const int x, const int y)
{
	return (x != pos.x && y != pos.y
		&& x >= 0 && y >= 0
		&& x < MAP_SIZE && y < MAP_SIZE);
}

size_t count_neighbors(const char *map, const t_player *player)
{
	size_t neighbors = 0;

	for (int x = player->pos.x - 1; x <= player->pos.x + 1; x++) {
		for (int y = player->pos.y - 1; y <= player->pos.y + 1; y++) {
			if (within_map(player->pos, x, y) &&
				(size_t)(map[CHARPOS(x, y)] - 48) != player->team &&
				map[CHARPOS(x, y)] != ' ' &&
				map[CHARPOS(x, y)] != '\n')
				neighbors++;
		}
	}
	if (neighbors != 0)
		printf("voisinsin : %ld\n", neighbors);
	return (neighbors);
}