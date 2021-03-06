/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** player
*/

#include "lemipc.h"

void move_player(char *map, t_player *player, const t_pos pos)
{
	if (pos.x < MAP_SIZE && pos.y < MAP_SIZE &&
			map[CHARPOS(pos.x, pos.y)] == ' ') {
		map[CHARPOS(player->pos.x, player->pos.y)] = ' ';
		map[CHARPOS(pos.x, pos.y)] = player->team + 48;
		player->pos.x = pos.x;
		player->pos.y = pos.y;
	}
}

int player_loop(t_player *player, t_id *id)
{
	char *map;

	while (1) {
		receive_message(id->msg_id, &id->msg, player->team);
		if (strcmp(id->msg.str, "quit") == 0)
			return (EXIT);
		get_rights(id);
		map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
		if (count_neighbors(map, player) >= 2)
			return (give_rights(id), EXIT);
		get_target(player, id, &player->target, map);
		move_player(map, player, move_to(player, map));
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
	id.sops.sem_flg = IPC_NOWAIT;
	player = create_player(team_number, &id);
	player_loop(&player, &id);
	delete_player(&player, &id);
	exit(SUCCESS);
}
