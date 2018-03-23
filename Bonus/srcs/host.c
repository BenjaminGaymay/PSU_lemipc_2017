/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** host
*/

#include "lemipc.h"

char *get_color_from_team(int team)
{
	switch(team) {
		case 1:
			return ("GREEN");
		case 2:
			return ("MAGENTA");
		case 3:
			return ("GREY");
		case 4:
			return ("GREEN");
		case 5:
			return ("YELLOW");
		case 6:
			return ("PURPLE");
		case 7:
			return ("ORANGE");
		case 8:
			return ("RED");
		case 9:
			return ("BLUE");
	}
	return (NULL);
}

int quit_loop(t_id *id)
{
	char *map;
	int last_team = 0;
	char *winner;

	while (1) {
		get_rights(id);
		map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
		if (nb_team_alive(map) == 0)
			break ;
		else {
			last_team = last_team_alive(map) - 48;
			send_msg(last_team, "quit", id);
		}
		give_rights(id);
		usleep(10000);
	}
	give_rights(id);
	asprintf(&winner, "Team %s win !", get_color_from_team(last_team));
	clear_window();
	refresh_window(0);
	print_text(0, -100, (SDL_Color){255, 255, 255, 127}, winner);
	refresh_window(0);
	sleep(5);
	delete_window();
	return (SUCCESS);
}

int host_loop(t_id *id)
{
	char *map;
	int prev_loop;

	init_window();
	while (1) {
		prev_loop = clear_window();
		if (manage_event() == EXIT)
			return (quit_loop(id));
		map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
		draw_arena();
		draw_array(map);
		refresh_window(prev_loop);
		receive_message(id->msg_id, &id->msg, HOST_ID);
		if (strcmp(id->msg.str, "quit") == 0)
			return (quit_loop(id));
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
	return (SUCCESS);
}
