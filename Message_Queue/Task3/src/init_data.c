#include "../include/msg_queue.h"

void 
send_init_data(mqd_t mqdes, struct DataChat *chat, const char *target_user)
{ /* предоставление истории/актвных польщователей чата новому пользовотелю*/
    char target_queue[32];
    snprintf(target_queue, sizeof(target_queue), "/mq_%s", target_user);
    mqd_t target_mq = mq_open(target_queue, O_WRONLY);
    
    // Отправляем список пользователей
    for (int i = 0; i < chat->usr_count; i++) {
        if (strcmp(chat->act_usrs[i], target_user) == 0) continue;
        struct Message user_msg = {INIT_USERS};
        strncpy(user_msg.sender, chat->act_usrs[i], MAX_USR_NAME);
        if (mq_send(target_mq, (char *)&user_msg, sizeof(user_msg), 0) == -1) {
            perror("mq_send init users");
        }
    }
    
    // Отправляем историю сообщений
    for (int i = 0; i < chat->msg_count; i++) {
        struct Message hist_msg = chat->msg_hist[i];
        hist_msg.type = INIT_HISTORY;
        if (mq_send(target_mq, (char *)&hist_msg, sizeof(hist_msg), 0) == -1) {
            perror("mq_send init history");
        }
    }
    mq_close(target_mq);
}
