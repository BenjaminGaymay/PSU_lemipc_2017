/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** manage_map
*/

#include "lemipc.h"

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

size_t last_team_alive(const char *map)
{
	for (size_t i = 0 ; map[i] ; i++) {
		if (map[i] != ' ' && map[i] != '\n')
			return (map[i]);
	}
	return (0);
}

int nb_team_alive(const char *map)
{
	int nb_team = 0;

	for (size_t i = 0 ; map[i] ; i++)
		nb_team = (map[i] != ' ' && map[i] != '\n' ? nb_team + 1 : nb_team);
	return (nb_team);
}