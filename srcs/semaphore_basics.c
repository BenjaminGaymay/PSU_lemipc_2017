/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** semaphore_basics
*/

#include "lemipc.h"

int get_rights(t_id *id)
{
	id->sops.sem_op = -1;
	while (semctl(id->sem_id, 0, GETVAL) == 0) {
		usleep(10000);
	}
	semop(id->sem_id, &id->sops, 1);
	return (SUCCESS);
}

void give_rights(t_id *id)
{
	id->sops.sem_op = 1;
	semop(id->sem_id, &id->sops, 1);
}

char *receive_message(const int msg_id, t_msg *msg, const int team)
{
	bzero(msg, sizeof(*msg));
	msgrcv(msg_id, msg, sizeof(*msg), team, IPC_NOWAIT);
	if (strcmp(msg->str, "") != 0)
		printf("Message reçu [%ld]: '%s'\n", msg->mtype, msg->str);
	return (msg->str);
}

void send_msg(const size_t team, const char *to_send, t_id *id)
{
	bzero(&id->msg, sizeof(id->msg));
	id->msg.mtype = team;
	sprintf(id->msg.str, to_send);
	msgsnd(id->msg_id, &id->msg, sizeof(id->msg), 0);
	printf("Je dis à %ld de : '%s'\n", team, id->msg.str);
}
