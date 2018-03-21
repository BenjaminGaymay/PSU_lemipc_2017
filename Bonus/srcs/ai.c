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

t_pos find_new_pos(const char *map, t_pos *pos)
{
	if (map[CHARPOS(pos->x+1, pos->y)] == ' ')
		pos->x++;
	else if (map[CHARPOS(pos->x-1, pos->y)] == ' ')
		pos->x--;
	else if ((map[CHARPOS(pos->x, pos->y+1)] == ' '))
		pos->y++;
	else if ((map[CHARPOS(pos->x, pos->y-1)] == ' '))
		pos->y--;
	return (*pos);
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
		npos = find_new_pos(map, &npos);
	return (npos);
}

size_t manhattan_dist(t_pos *p1, t_pos *p2)
{
	return abs(p1->x + p2->x) - abs(p1->y + p2->y);
}

t_pos look_ennemy(const char *map, t_pos *p, size_t team)
{
	t_pos pos;
	t_pos ennemy = {-1, -1};
	int min = -1;
	int dist;

	for (size_t i = 0; map[i] ; i++) {
		if (map[i] != ' '  && map[i] != '\n' && (size_t)(map[i] - 48) != team) {
			pos.x = i % (MAP_SIZE + 1);
			pos.y = i / (MAP_SIZE + 1);
			dist = manhattan_dist(&pos, p);
			if (dist < min || min == -1) {
				min = dist;
				memcpy(&ennemy, &pos, sizeof(pos));
			}
		}
	}
	return (ennemy);
}

static size_t line_neighbors(const char *map, t_pos *pos, size_t team)
{
	size_t neighbors = 0;

	for (int i = pos->x - 1; i <= pos->x + 1; i++) {
		if (i >= 0 && i < MAP_SIZE &&
			pos->y >= 0 && pos->y < MAP_SIZE &&
			(size_t)(map[CHARPOS(i, pos->y)] - 48) != team &&
			map[CHARPOS(i, pos->y)] != ' ' &&
			map[CHARPOS(i, pos->y)] != '\n' &&
			map[CHARPOS(i, pos->y)] != '\0')
			neighbors++;
	}
	return (neighbors);
}

size_t count_neighbors(const char *map, const t_player *player)
{
	size_t neighbors = 0;
	t_pos pos;

	pos.x = player->pos.x;
	pos.y = player->pos.y - 1;
	neighbors += line_neighbors(map, &pos, player->team);
	pos.y = player->pos.y;
	neighbors += line_neighbors(map, &pos, player->team);
	pos.y = player->pos.y + 1;
	neighbors += line_neighbors(map, &pos, player->team);
	return (neighbors);
}