#include "../include/msg_queue.h"

void
get_msg (mqd_t mqdes, char msg[MAX_MSG_LEN], unsigned int *msg_prio) 
{
    ssize_t rec_msg;

    if ((rec_msg = mq_receive(mqdes, msg, MAX_MSG_LEN, msg_prio)) == -1) {
        perror("mq_receive");
        exit(EXIT_FAILURE);
    } else {
        msg[rec_msg] = '\0'; 
        printf("%s", msg);
    }
}
