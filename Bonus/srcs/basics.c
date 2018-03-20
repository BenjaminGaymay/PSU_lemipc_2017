/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** basics
*/

#include "lemipc.h"

int is_number(const char *str)
{
	for (size_t i = 0 ; str[i] ; i++) {
		if (isdigit(str[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

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
