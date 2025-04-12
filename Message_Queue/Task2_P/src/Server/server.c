#include "../../include/msg_queue.h"

int
main (void)
{
    char msg[MAX_MSG_LEN];
    struct mq_attr attr, *attrp;
    unsigned int msg_prio;
    mqd_t mqdes;
    
    attr.mq_maxmsg = 4;
    attr.mq_msgsize = MAX_MSG_LEN;
    attrp = &attr;

    if ((mqdes = mq_open(PATH_QUEUE, O_RDWR | O_CREAT, 0664, attrp)) == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    get_msg(mqdes, msg, &msg_prio);
    
    strncpy(msg, "Hi!\n", MAX_MSG_LEN - 1);
    msg[MAX_MSG_LEN - 1] = '\0';
    msg_prio = 1;

    send_msg(mqdes, msg, msg_prio);
    
    if (mq_close(mqdes) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    if (mq_unlink(PATH_QUEUE) == -1) {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
