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
#include <stdbool.h>

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR 84
# define EXIT 1

# define TRUE 1
# define FALSE 0

# define KEY_ERROR -1
# define SHM_ERROR -1

# define MAP_SIZE 30
# define MALLOC_MAP (MAP_SIZE + 1) * MAP_SIZE

# define CHARPOS(x, y) (x) + (y) * (MAP_SIZE + 1)

# define NONE -1

# define HOST_ID 255
# define MSG_COPY 040000

typedef struct s_pos {
	int x;
	int y;
} t_pos;

typedef struct s_player {
	t_pos pos;
	t_pos target;
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

/*
** manage_map
*/
char *create_map(char *);
void show_map(const char *);
size_t last_team_alive(const char *);
int nb_team_alive(const char *);

/*
** semaphore_basics
*/
int get_rights(t_id *id);
void give_rights(t_id *);
char *receive_message(const int, t_msg *, const int);
void send_msg(const size_t, const char *, t_id *);

/*
** basics
*/
int is_number(const char *);
int print_help(int);
int print_error(const char *, const int);

/*
** host
*/
int host(const key_t);

/*
** player
*/
int player(const key_t, const size_t);

/*
** add_remove_player
*/
t_player create_player(const size_t, t_id *);
void delete_player(t_player *, t_id *);

/*
** ai
*/
t_pos move_to(t_player *, const char *);
t_pos look_ennemy(const char *, t_pos *, size_t);
size_t count_neighbors(const char *, const t_player *);


/*
** strategy
*/
void get_target(t_player *, t_id *, t_pos *, const char *);
