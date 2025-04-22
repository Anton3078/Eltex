#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>

#define PATH_QUEUE_MSG "/mq_msg"
#define PATH_QUEUE_USR "/mq_usr"
#define MAX_MSG_LEN 1024
#define MAX_MSG 4
#define MAX_USR 4
#define MAX_USR_NAME 32

enum MsgType { USER_JOIN, CHAT_MSG, USER_LEAVE };

struct Message {
    enum MsgType type;
    char user[MAX_USR_NAME];
    char mtext[MAX_MSG_LEN];
};

void add_user(const char *, char [MAX_USR][MAX_USR_NAME], int *);
void remove_user(const char *, char [MAX_USR][MAX_USR_NAME], int *);
void broadcast(mqd_t, struct Message *, char [MAX_USR][MAX_USR_NAME], int);

#endif
