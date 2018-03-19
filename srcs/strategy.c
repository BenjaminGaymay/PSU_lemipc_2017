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
	t_pos pos;
	char msg[32];

	if (strncmp(id->msg.str, "target", 6) == 0) {
		pos = get_pos_from_msg(&id->msg.str[7]);
		memcpy(&player->target, &pos, sizeof(pos));
	}
	else if (target->x == NONE || target->y == NONE ||
			map[CHARPOS(target->x, target->y)] == ' ') {
		pos = look_ennemy(map, player);
		bzero(msg, sizeof(msg));
		sprintf(msg, "target:%d,%d", pos.x, pos.y);
		send_msg(player->team, msg, id);
		memcpy(&player->target, &pos, sizeof(pos));
	}
}