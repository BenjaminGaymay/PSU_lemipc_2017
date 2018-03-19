/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** add_remove_player
*/

#include "lemipc.h"

void delete_player(t_player *player, t_id *id)
{
	char *map;

	get_rights(id);
	map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
	map[CHARPOS(player->pos.x, player->pos.y)] = ' ';
	printf("'%ld': je suis mort en [%d, %d]\n", player->team, player->pos.x, player->pos.y);
	if (player->team != last_team_alive(map) - 48 && nb_team_alive(map) == 1) {
		give_rights(id);
		return (send_msg(HOST_ID, "quit", id));
	}
	give_rights(id);
}

void add_player(char *map, t_player *player, const size_t team_number)
{
	int x = rand() % MAP_SIZE;
	int y = rand() % MAP_SIZE;

	while (map[CHARPOS(x, y)] != ' ') {
		x = rand() % MAP_SIZE;
		y = rand() % MAP_SIZE;
	}
	usleep(rand() % 5432 + 5432);
	player->pos.x = x;
	player->pos.y = y;
	player->target.x = NONE;
	player->target.y = NONE;
	player->team = team_number;
	map[CHARPOS(x, y)] = team_number + 48;
}

t_player create_player(const size_t team_number, t_id *id)
{
	t_player player;
	char *map;

	get_rights(id);
	map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
	add_player(map, &player, team_number);
	give_rights(id);
	return (player);
}
