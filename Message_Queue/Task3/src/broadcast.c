#include "../include/msg_queue.h"

void
broadcast(mqd_t mqdes, struct Message *msg, struct DataChat *chat)
{ /* рассылка сообщения всем клиентам*/
     for (int i = 0; i < chat->usr_count; i++) {
        
        char target_queue[32];
        mqd_t target_mq;
        snprintf(target_queue, sizeof(target_queue), "/mq_%s", chat->act_usrs[i]);
        if ((target_mq = mq_open(target_queue, O_WRONLY)) == -1) {
            perror("mq_open");
            continue;
        }

        if (mq_send(target_mq, (char *)msg, sizeof(struct Message), 0) == -1) {
           perror("mq_send");
        }
        mq_close(target_mq);
    }
}
