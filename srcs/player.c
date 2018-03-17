/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** player
*/

#include "lemipc.h"

void move_player(char *map, t_player *player, const int x, const int y)
{
	if (map[CHARPOS(x, y)] == ' ') {
		map[CHARPOS(player->x, player->y)] = ' ';
		map[CHARPOS(x, y)] = player->team + 48;
		player->x = x;
		player->y = y;
	}
}

int player_loop(t_player *player, t_id *id)
{
	char *map;

	while (player->y + 1 < MAP_SIZE) {
		get_rights(id);
		map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
		move_player(map, player, player->x, player->y + 1);
		if (receive_message(id->msg_id, &id->msg, player->team, "quit") == SUCCESS)
			return (give_rights(id), EXIT);
		give_rights(id);
		usleep(100000);
	}
	return (SUCCESS);
}

int player(const key_t key, const size_t team_number)
{
	t_id id;
	t_player player;

	id.shm_id = shmget(key, MALLOC_MAP, SHM_R | SHM_W);
	id.sem_id = semget(key, 0, SHM_R | SHM_W);
	id.msg_id = msgget(key, SHM_R | SHM_W);
	id.sops.sem_num = 0;
	id.sops.sem_flg = 0;
	player = create_player(team_number, &id);
	if (player_loop(&player, &id) == SUCCESS)
		delete_player(&player, &id);
	return (SUCCESS);
}
