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
	map[CHARPOS(player->x, player->y)] = ' ';
	give_rights(id);
	if (nb_team_alive(map) == 1) {
		send_msg(last_team_alive(map) - 48, "quit", id);
		return send_msg(HOST_ID, "quit", id);
	}
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
	player->x = x;
	player->y = y;
	player->target_x = NONE;
	player->target_y = NONE;
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
