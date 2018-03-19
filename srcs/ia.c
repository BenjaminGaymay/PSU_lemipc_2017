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

size_t min(size_t a, size_t b)
{
	return (a <= b ? a : b);
}

t_pos look_ennemy(const char *map, t_player *p)
{
	t_pos pos;
	t_pos ennemy = {-1, -1};
	size_t min = 0;
	size_t dist;

	for (size_t i = 0; i < strlen(map); i++) {
		if (map[i] >= '1' && map[i] <= '9' && (size_t)(map[i] - 48) != p->team) {
			pos.x = i % MAP_SIZE;
			pos.y = i / MAP_SIZE;
			dist = manhattan_dist(&pos, &p->pos);
			if (min == 0) {
				min = dist;
				memcpy(&ennemy, &pos, sizeof(pos));
			}
			if (dist < min)
				memcpy(&ennemy, &pos, sizeof(pos));
		}
	}
	return ennemy;
}

static int within_map(const char *map, const t_pos pos, const int i, const int j)
{
	return (i != pos.x && j != pos.y && i >= 0 && j >= 0 &&
		 i < i / MAP_SIZE && j < j % MAP_SIZE);
}

size_t count_neighbors(const char *map, const t_player *player)
{
	size_t neighbors = 0;

	for (int i = player->pos.x - 1; i < player->pos.x + 1; i++) {
		for (int j = player->pos.y - 1; j < player->pos.y + 1; j++) {
			if (within_map(map, player->pos, i, j))
				neighbors++;
		}
	}
	return (neighbors);
}