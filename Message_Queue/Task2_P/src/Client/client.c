#include "../../include/msg_queue.h"

int main(int argc, char *argv[])
{
    char msg[MAX_MSG_LEN];
    unsigned int msg_prio;
    mqd_t mqdes;

    if ((mqdes = mq_open(PATH_QUEUE, O_RDWR)) == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    } 
    
    strncpy(msg, "Hello\n", MAX_MSG_LEN - 1);
    msg[MAX_MSG_LEN - 1] = '\0';
    msg_prio = 1;
    
    send_msg(mqdes, msg, msg_prio);
    get_msg(mqdes, msg, &msg_prio);
    
    if (mq_close(mqdes) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
