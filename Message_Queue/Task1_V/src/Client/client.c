#include "../include/msg_queue.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
    key_t key;
    struct MsgBuf *msg;
    int queue_id;

    if (!(msg = malloc(sizeof(struct MsgBuf)))) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if ((key = ftok(PATH_QUEUE, PROJ_ID)) == -1) {
        perror("ftok");
        free(msg);
        exit(EXIT_FAILURE);
    }

    if ((queue_id = msgget(key, 0664)) == -1) {
        perror("msgget");
        free(msg);
        exit(EXIT_FAILURE);
    }
    
    strncpy(msg->mtext, "Hello\n", MAX_MSG_LEN - 1);
    msg->mtext[MAX_MSG_LEN - 1] = '\0'; 
    msg->mtype = 1;

    send_msg(queue_id, msg);
    get_msg(queue_id, msg->mtype);

    free(msg); 
    exit(EXIT_SUCCESS);
}
