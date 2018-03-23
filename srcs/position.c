/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** position
*/

#include "lemipc.h"

size_t manhattan_dist(t_pos *p1, t_pos *p2)
{
	return abs(p1->x + p2->x) - abs(p1->y + p2->y);
}

int get_new_pos(int player, int target)
{
	if (player < target && player + 1 < MAP_SIZE)
		return (player + 1);
	else if (player > target && player - 1 >= 0)
		return (player - 1);
	return (player);
}

t_pos find_new_pos(const char *map, t_pos *pos)
{
	int cpy_x = pos->x;

	if (pos->x + 1 < MAP_SIZE && map[CHARPOS(pos->x+1, pos->y)] == ' ')
		pos->x++;
	else if (pos->x - 1 >= 0 && map[CHARPOS(pos->x-1, pos->y)] == ' ')
		pos->x--;
	if (pos->y + 1 < MAP_SIZE && map[CHARPOS(pos->x, pos->y + 1)] == ' '
		&& cpy_x == pos->x)
		pos->y++;
	else if (pos->y - 1 >= 0 && map[CHARPOS(pos->x, pos->y - 1)] == ' '
		&& cpy_x == pos->x)
		pos->y--;
	return (*pos);
}