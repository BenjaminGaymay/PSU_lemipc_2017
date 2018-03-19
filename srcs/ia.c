/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** ia
*/

#include "lemipc.h"

int get_new_pos(int player, int target)
{
	if (player < target)
		return (player + 1);
	else if (player > target)
		return (player - 1);
	return (player);
}

t_pos move_to(t_player *player, const char *map)
{
	t_pos npos;

	if (player->target.x == NONE || player->target.y == NONE)
		return (player->pos);
	memcpy(&npos, &player->pos, sizeof(npos));
	npos.x = get_new_pos(player->pos.x, player->target.x);
	if (npos.x == player->pos.x)
		npos.y = get_new_pos(player->pos.y, player->target.y);
	if (map[CHARPOS(npos.x, npos.y)] != ' ')
		npos.y = get_new_pos(player->pos.y, player->target.y);
	return (npos);
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