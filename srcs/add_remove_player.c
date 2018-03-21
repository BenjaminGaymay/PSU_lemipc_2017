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
	if (player->team != last_team_alive(map) - 48 && nb_team_alive(map) == 1) {
		give_rights(id);
		send_msg(HOST_ID, "quit", id);
		return;
	}
	give_rights(id);
}

void add_player(char *map, t_player *player)
{
	int x = player->pos.x;
	int y = player->pos.y;

	while (map[CHARPOS(x, y)] != ' ') {
		x = rand() % MAP_SIZE;
		y = rand() % MAP_SIZE;
	}
	map[CHARPOS(x, y)] = player->team + 48;
	player->pos.x = x;
	player->pos.y = y;
}

void init_player(t_player *player, const size_t team_number)
{
	player->pos.x = rand() % MAP_SIZE;
	player->pos.y = rand() % MAP_SIZE;
	player->target.x = NONE;
	player->target.y = NONE;
	player->team = team_number;
}

t_player create_player(const size_t team_number, t_id *id)
{
	t_player player;
	char *map;

	srand(time(NULL));
	init_player(&player, team_number);
	get_rights(id);
	map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
	add_player(map, &player);
	give_rights(id);
	return (player);
}
