/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** strategy
*/

#include "lemipc.h"

t_pos get_pos_from_msg(char *msg)
{
	t_pos pos;
	int i = 0;

	for (i = 0 ; msg[i] != ',' ; i++)
		;
	msg[i] = '\0';
	pos.x = atoi(msg);
	pos.y = atoi(&msg[i + 1]);
	return (pos);
}

void get_target(t_player *player, t_id *id, t_pos *target, const char *map)
{
	t_pos pos = {MAP_SIZE / 2, MAP_SIZE / 2};
	char msg[32] = {'\0'};

	if (id->msg.str && strncmp(id->msg.str, "target:", 7) == 0) {
		pos = get_pos_from_msg(&id->msg.str[7]);
		memcpy(&player->target, &pos, sizeof(pos));
		return;
	}
	else if (target->x == NONE || target->y == NONE)
		pos = look_ennemy(map, &player->pos, player->team);
	else if (map[CHARPOS(target->x, target->y)] == ' ')
		pos = look_ennemy(map, &player->target, player->team);
	bzero(msg, sizeof(msg));
	sprintf(msg, "target:%d,%d", pos.x, pos.y);
	send_msg(player->team, msg, id);
	memcpy(&player->target, &pos, sizeof(pos));
}