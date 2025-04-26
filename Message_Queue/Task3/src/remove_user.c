#include "../include/msg_queue.h"

void
remove_user(const char *username, struct DataChat *chat) 
{ /* удаление пользователя со сдвигом*/
    if (chat->usr_count == 0) return;

    for (int i = 0; i < chat->usr_count; ++i) {
        if (strcmp(chat->act_usrs[i], username) == 0) {
            for (int j = i; j < chat->usr_count - 1; ++j) {
                strncpy(chat->act_usrs[j], chat->act_usrs[j + 1], MAX_USR_NAME);
            }
            memset(chat->act_usrs[chat->usr_count - 1], 0, MAX_USR_NAME);
            chat->usr_count--;
            return;
        }
    }
}
