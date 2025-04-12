#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PATH_QUEUE "/tmp/my_msg_queue"
#define PROJ_ID 'A'
#define MAX_MSG_LEN 32

struct MsgBuf {
    long mtype;
    char mtext[MAX_MSG_LEN];
};

extern void get_msg(int, int);
extern void send_msg(int, struct MsgBuf *);

#endif
