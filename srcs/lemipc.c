/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** lemipc
*/

#include "lemipc.h"

int init_lemipc(const char *path, size_t team_number)
{
	key_t key;
	int shm_id;

	if (team_number == 0)
		return (ERROR);
	key = ftok(path, 0);
	if (key == KEY_ERROR)
		return (print_error("Error : ftok failed", ERROR));
	shm_id = shmget(key, MALLOC_MAP, SHM_R | SHM_W);
	if (shm_id == SHM_ERROR)
		return (host(key));
	return (player(key, team_number));
}

int main(const int ac, const char **av)
{
	if (ac == 2 && av[1] != NULL && (strcmp(av[1], "--help") == 0))
		return print_help(SUCCESS);
	else if (ac != 3 || av[1] == NULL || av[2] == NULL ||
			is_number(av[2]) == FALSE)
		return print_help(ERROR);
	return (init_lemipc(av[1], atoi(av[2])));
}
