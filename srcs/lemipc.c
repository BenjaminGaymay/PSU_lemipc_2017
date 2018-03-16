/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** lemipc
*/

#include "lemipc.h"

int print_help(int ret)
{
	printf("%s", "USAGE\n       ./lempic PATH TEAM_NUMBER\n\nDESCRIPTION");
	printf("%s", "\n       PATH         path you\'ll give to ftok\n     ");
	printf("%s", "  TEAM_NUMBER  team number of the current champion");
	printf("%s", " (greater than 0)\n");

	return (ret);
}

int print_error(const char *msg, const int ret)
{
	fprintf(stderr, "%s\n", msg);
	return (ret);
}

char *create_map(char *map)
{
	for (size_t i = 0 ; i < MALLOC_MAP ; i++)
		map[i] = (i % (MAP_SIZE + 1) == 0 ? '\n' : ' ');
	return (&map[1]);
}

void show_map(const char *map)
{
	for (size_t i = 0 ; i < MAP_SIZE + 1 ; i++)
		printf("%c", '#');

	printf("#\n#");
	for (size_t i = 0 ; map[i] ; i++)
		printf((map[i] == '\n' ? "#\n#" : "%c"), map[i]);

	printf("#\n#");
	for (size_t i = 0 ; i < MAP_SIZE + 2 ; i++)
		printf("%c", (i == MAP_SIZE + 1 ? '\n' : '#'));
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

	id->sops.sem_op = -1;

	while (semctl(id->sem_id, 0, GETVAL) == 0) {
		usleep(10000); // recherche toussa toussa
	}
	semop(id->sem_id, &id->sops, 1); // Je prend le controle

	map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
	add_player(map, &player, team_number);

	id->sops.sem_op = 1;
	semop(id->sem_id, &id->sops, 1); // Je redonne le controle
	return (player);
}

void move_player(char *map, t_player *player, const int x, const int y)
{
	if (map[CHARPOS(x, y)] == ' ') {
		map[CHARPOS(player->x, player->y)] = ' ';
		map[CHARPOS(x, y)] = player->team + 48;
		player->x = x;
		player->y = y;
	}
	printf("%ld [%d, %d]\n", player->team, player->x, player->y);
}

int player_loop(t_player *player, t_id *id)
{
	char *map;

	id->sops.sem_op = -1;
	while (semctl(id->sem_id, 0, GETVAL) == 0) {
		usleep(10000); // recherche toussa toussa
	}
	semop(id->sem_id, &id->sops, 1); // Je prend le controle

	map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;
	move_player(map, player, player->x, player->y + 1);
	id->sops.sem_op = 1;
	semop(id->sem_id, &id->sops, 1); // Je redonne le controle
	return (SUCCESS);
}

int nb_team_alive(const char *map)
{
	int nb_team = 0;

	for (size_t i = 0 ; map[i] ; i++)
		nb_team = (map[i] != ' ' && map[i] != '\n' ? nb_team + 1 : nb_team);

	return (nb_team);
}

void send_msg(const size_t team, const char *to_send, t_id *id)
{
	bzero(&id->msg, sizeof(id->msg));
	id->msg.mtype = team;
	sprintf(id->msg.str, to_send);
	msgsnd(id->msg_id, &id->msg, sizeof(id->msg), 0);
}

void delete_player(t_player *player, t_id *id)
{
	char *map;

	id->sops.sem_op = -1;
	while (semctl(id->sem_id, 0, GETVAL) == 0) {
		usleep(10000); // recherche toussa toussa
	}

	semop(id->sem_id, &id->sops, 1); // Je prend le controle

	map = (char *)shmat(id->shm_id, NULL, SHM_R | SHM_W) + 1;

	map[CHARPOS(player->x, player->y)] = ' ';
	if (nb_team_alive(map) == 1) {
		send_msg(HOST_ID, "quit", id);
		return ;
	}

	id->sops.sem_op = 1;
	semop(id->sem_id, &id->sops, 1); // Je redonne le controle
}

int player(const key_t key, const size_t team_number)
{
	t_id id;
	t_player player;

	id.shm_id = shmget(key, MALLOC_MAP, SHM_R | SHM_W); // Get SHM
	id.sem_id = semget(key, 0, SHM_R | SHM_W); // Get SEM
	id.msg_id = msgget(key, SHM_R | SHM_W);

	id.sops.sem_num = 0;
	id.sops.sem_flg = 0;

	player = create_player(team_number, &id);

	while (player.y + 1 < MAP_SIZE) {
		player_loop(&player, &id);
		msgrcv(id.msg_id, &id.msg, sizeof(id.msg), player.team, IPC_NOWAIT);
		if (strcmp(id.msg.str, "quit") == 0)
			break ;
		usleep(100000);
	}
	delete_player(&player, &id);
	return (SUCCESS);
}

int host(const key_t key)
{
	int shm_id;
	int sem_id;
	int msg_id;
	t_msg msg;
	char *map;

	shm_id = shmget(key, MALLOC_MAP, IPC_CREAT | SHM_R | SHM_W); // Create SHM
	sem_id = semget(key, 1, IPC_CREAT | SHM_R | SHM_W); // Create SEM
	msg_id = msgget(key, IPC_CREAT | SHM_R | SHM_W); // Create MSG
	semctl(sem_id, 0, SETVAL, 1); // Init SEM

	map = create_map((char *)shmat(shm_id, NULL, SHM_R | SHM_W)); // Get SHM

	while (1) {
		system("clear");
		show_map(map);
		msgrcv(msg_id, &msg, sizeof(msg), HOST_ID, IPC_NOWAIT);
		if (strcmp(msg.str, "quit") == 0)
			break ;
		usleep(100000);
	}
	shmctl(shm_id, IPC_RMID, NULL);
	semctl(sem_id, IPC_RMID, 0, NULL);
	msgctl(msg_id, IPC_RMID, NULL);
	return (SUCCESS);
}

int init_lemipc(const char *path, const size_t team_number)
{
	key_t key;
	int shm_id;

	key = ftok(path, 0);
	printf("Key : %d\n", key);
	if (key == KEY_ERROR)
		return (print_error("Error : ftok failed", ERROR));

	shm_id = shmget(key, MALLOC_MAP, SHM_R | SHM_W);
	if (shm_id == SHM_ERROR)
		host(key);
	else
		player(key, team_number);
	return (SUCCESS);
}

int is_number(const char *str)
{
	for (size_t i = 0 ; str[i] ; i++) {
		if (isdigit(str[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int main(const int ac, const char **av)
{
	srand(time(NULL));
	if (ac == 2 && av[1] != NULL && (strcmp(av[1], "--help") == 0))
		return print_help(SUCCESS);
	else if (ac != 3 || av[1] == NULL || av[2] == NULL ||
			is_number(av[2]) == FALSE)
		return print_help(ERROR);
	return (init_lemipc(av[1], atoi(av[2])));
}
