/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** host
*/

#include "lemipc.h"

int host_loop(t_id *id)
{
	char *map;
	while (1) {
		system("clear");
		get_rights(id);
		map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
		show_map(map);
		give_rights(id);
		if (receive_message(id->msg_id, &id->msg,
				HOST_ID, "quit") == SUCCESS) {
			usleep(100000);
			return (SUCCESS);
		}
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
	id.sops.sem_flg = 0;
	create_map((char *)shmat(id.shm_id, NULL, SHM_R | SHM_W));
	semctl(id.sem_id, 0, SETVAL, 1);
	host_loop(&id);
	shmctl(id.shm_id, IPC_RMID, NULL);
	semctl(id.sem_id, IPC_RMID, 0, NULL);
	msgctl(id.msg_id, IPC_RMID, NULL);
	printf("Je quitte normalement, ca segv sur un return 0 c'est super cool omg\n");
	return (SUCCESS);
}