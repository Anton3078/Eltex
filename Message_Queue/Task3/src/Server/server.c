#include "../../include/msg_queue.h"

int main() {
    mqd_t mqdes_usr, mqdes_msg;
    unsigned int msg_prio = 0;
    struct mq_attr attr, *attrp;
    
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = sizeof(struct Message);
    attr.mq_flags = 0;
    attrp = &attr;
    
    mq_unlink(PATH_QUEUE_USR);
    mq_unlink(PATH_QUEUE_MSG);
    
    if ((mqdes_usr = mq_open(PATH_QUEUE_USR, O_RDWR | O_CREAT, 0666, attrp)) == (mqd_t)-1) {
        perror("mq_open_usr");
        exit(EXIT_FAILURE);
    }

    if ((mqdes_msg = mq_open(PATH_QUEUE_MSG, O_RDWR | O_CREAT, 0666, attrp)) == (mqd_t)-1) {
        perror("mq_open_msg");
        exit(EXIT_FAILURE);
    }

    char active_users[MAX_USR][MAX_USR_NAME];
    int user_count = 0;
    
    printf("===Server is starting===\n");
    
    while (1) {
        struct Message msg;
        if (mq_receive(mqdes_usr, (char *)&msg, sizeof(msg), &msg_prio) == -1) {
            perror("mq_receive");
            continue;
        }

        switch (msg.type) {
            case USER_JOIN:
                add_user(msg.user, active_users, &user_count);
                broadcast(mqdes_msg, &msg, active_users, user_count);
                printf("User: %s joined the chat\tUser count:%d\n", msg.user, user_count);
                break;
            case CHAT_MSG:
                broadcast(mqdes_msg, &msg, active_users, user_count);
                break;
            case USER_LEAVE:
                remove_user(msg.user, active_users, &user_count);
                broadcast(mqdes_msg, &msg, active_users, user_count);
                printf("User: %s left the chat\tUser count:%d\n", msg.user, user_count);
                break;
       }
    }

    mq_close(mqdes_usr);
    mq_close(mqdes_msg);
    mq_unlink(PATH_QUEUE_USR);
    mq_unlink(PATH_QUEUE_MSG);
    return 0;
}
