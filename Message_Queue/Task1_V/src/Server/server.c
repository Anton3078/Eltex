#include "../include/msg_queue.h"
#include <string.h>
#include <malloc.h>

int
main (int argc, char *argv[])
{
    key_t key;
    struct MsgBuf *msg;
    int queue_id;
    
    if(!(msg = malloc(sizeof(struct MsgBuf)))) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if ((key = ftok(PATH_QUEUE, PROJ_ID)) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    if ((queue_id = msgget(key, 0664 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    
    get_msg(queue_id, msg->mtype);

    strncpy(msg->mtext, "Hi!\n", MAX_MSG_LEN - 1);
    msg->mtext[MAX_MSG_LEN - 1] = '\0';
    msg->mtype = 1;
     
    send_msg(queue_id, msg);
    
    if (msgctl(queue_id, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
