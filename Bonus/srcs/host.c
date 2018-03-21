/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** host
*/

#include "lemipc.h"

int quit_loop(t_id *id)
{
	char *map;

	while (1) {
		get_rights(id);
		map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
		if (nb_team_alive(map) == 0)
			break ;
		else
			send_msg(last_team_alive(map) - 48, "quit", id);
		give_rights(id);
		usleep(10000);
	}
	return (SUCCESS);
}

int host_loop(t_id *id)
{
	char *map;

	init_window();
	while (1) {
		if (manage_event() == EXIT)
			return (quit_loop(id));
		get_rights(id);
		map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
		clear_window();
		draw_arena();
		draw_array(map);
		refresh_window();
		give_rights(id);
		receive_message(id->msg_id, &id->msg, HOST_ID);
		if (strcmp(id->msg.str, "quit") == 0)
			return (quit_loop(id));
		usleep(100000);
	}
	return (SUCCESS);
}

int host(const key_t key)
{
	t_id id;

	id.shm_id = shmget(key, MALLOC_MAP, IPC_CREAT | SHM_R | SHM_W);
	id.sem_id = semget(key, 1, IPC_CREAT | SHM_R | SHM_W);
	id.msg_id = msgget(key, IPC_CREAT | SHM_R | SHM_W);
	id.sops.sem_num = 0;
	id.sops.sem_flg = IPC_NOWAIT;
	create_map((char *)shmat(id.shm_id, NULL, SHM_R | SHM_W));
	semctl(id.sem_id, 0, SETVAL, 1);
	host_loop(&id);
	msgctl(id.msg_id, IPC_RMID, NULL);
	semctl(id.sem_id, IPC_RMID, 0, NULL);
	shmctl(id.shm_id, IPC_RMID, NULL);
	return (SUCCESS); // POURQUOI ?!
}