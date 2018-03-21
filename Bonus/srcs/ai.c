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

// t_pos dfs(t_pos *target, t_pos *start)
// {
// 	t_pos pos;

// 	if (start->x == target->x && start->y == target->y)
// 		return (*start);

// 	return (pos);
// }

static bool within_map(const t_pos pos, const int x, const int y)
{
	return (x != pos.x && y != pos.y
		&& x >= 0 && y >= 0
		&& x <= MAP_SIZE && y <= MAP_SIZE);
}

size_t count_neighbors(const char *map, const t_player *player)
{
	size_t neighbors = 0;

	for (int x = player->pos.x - 1; x <= player->pos.x + 1; x++) {
		for (int y = player->pos.y - 1; y <= player->pos.y + 1; y++) {
			if (within_map(player->pos, x, y) &&
				(size_t)(map[CHARPOS(x, y)] - 48) != player->team &&
				map[CHARPOS(x, y)] != ' ' &&
				map[CHARPOS(x, y)] != '\n' &&
				map[CHARPOS(x, y)] != '\0') {
				neighbors += 1;
			}
		}
	}
	return (neighbors);
}