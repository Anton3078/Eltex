#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

#define PATH_QUEUE "/my_msg_queue"
#define MAX_MSG_LEN 1024


extern void get_msg(mqd_t, char [MAX_MSG_LEN], unsigned int *);
extern void send_msg(mqd_t, char [MAX_MSG_LEN], unsigned int);

#endif
