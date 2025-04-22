#include "../include/msg_queue.h"

void
broadcast(mqd_t mqdes, struct Message *msg, char users[MAX_USR][MAX_USR_NAME], int usr_count)
{
    for (int i = 0; i < usr_count; ++i) {
        if (mq_send(mqdes, (char *)msg, sizeof(struct Message), 0) == -1) {
            perror("mq_send");
        }
    }
}
