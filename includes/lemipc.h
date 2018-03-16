/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** lemipc
*/

#pragma once

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR 84

# define TRUE 1
# define FALSE 0

# define KEY_ERROR -1
# define SHM_ERROR -1

# define MAP_SIZE 30
# define MALLOC_MAP (MAP_SIZE + 1) * MAP_SIZE

# define CHARPOS(x, y) (x) + (y) * (MAP_SIZE + 1)

# define NONE -1

# define HOST_ID sizeof(char)

typedef struct s_player {
	int x;
	int y;
	int target_x;
	int target_y;
	size_t team;
} t_player;

typedef struct s_msg {
	long int mtype;
	char str[32];
} t_msg;

typedef struct s_id {
	int shm_id;
	int sem_id;
	int msg_id;
	struct sembuf sops;
	t_msg msg;
} t_id;