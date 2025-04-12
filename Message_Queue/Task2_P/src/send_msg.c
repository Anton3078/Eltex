#include "../include/msg_queue.h"

void
send_msg(mqd_t mqdes, char msg[MAX_MSG_LEN], unsigned int msg_prio)  
{
    if (mq_send(mqdes, msg, strlen(msg), msg_prio) == -1) {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }
}
