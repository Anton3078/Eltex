#include "../../include/msg_queue.h"

int 
main() 
{
    mqd_t mqdes_usr;
    struct mq_attr attr;
    
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = sizeof(struct Message);
    attr.mq_flags = 0;
    
    struct DataChat chat = {0};

    mq_unlink(PATH_QUEUE_USR);
    
    if ((mqdes_usr = mq_open(PATH_QUEUE_USR, O_RDONLY | O_CREAT, 0664, &attr)) == (mqd_t)-1) {
        perror("mq_open_usr");
        exit(EXIT_FAILURE);
    }

    printf("===Server is starting===\n");
    
    while (1) {
        struct Message msg = {0};
        if (mq_receive(mqdes_usr, (char *)&msg, sizeof(msg), NULL) == -1) {
            perror("mq_receive");
            continue;
        }

        switch (msg.type) {
            case USER_JOIN:
               if (chat.usr_count >= MAX_USR) {
                    fprintf(stderr, "User limit reached\n");
                    continue;
                }
                add_user(msg.sender, &chat);
    
                char client_queue[32];
                snprintf(client_queue, sizeof(client_queue), "/mq_%s", msg.sender);
                mqd_t client_mq = mq_open(client_queue, O_WRONLY | O_CREAT, 0664, &attr);
    
                send_init_data(client_mq, &chat, msg.sender);
                broadcast(mqdes_usr, &msg, &chat);
                printf("[+] %s joined. Users: %d\n", msg.sender, chat.usr_count);
                mq_close(client_mq);
                break; 
            
            case CHAT_MSG:
                if (chat.msg_count < MAX_MSG) {
                    chat.msg_hist[chat.msg_count++] = msg;
                } else {
                    for (int i = 0; i < chat.msg_count; i++) {
                        chat.msg_hist[i] = chat.msg_hist[i + 1];
                    }
                    chat.msg_hist[MAX_MSG - 1] = msg;

                }
                broadcast(mqdes_usr, &msg, &chat);
                printf("[#] %s send message\n", msg.sender);
                break; 
            
            case USER_LEAVE:
                remove_user(msg.sender, &chat);
                broadcast(mqdes_usr, &msg, &chat);
                printf("[-] %s left. User: %d\n", msg.sender, chat.usr_count);
                break;

            default:
                fprintf(stderr, "Unknow message type\n");
        }
    }

    mq_close(mqdes_usr);
    mq_unlink(PATH_QUEUE_USR);
    exit(EXIT_FAILURE);
}
