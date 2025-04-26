#include "../include/msg_queue.h"

void 
add_user(const char *username, struct DataChat *chat) 
{ /*  доабвление новых пользователей*/
    if (chat->usr_count >= MAX_USR) {
        fprintf(stderr, "User limit reached\n");
        return;
    }
    
    if (strlen(username) >= MAX_USR_NAME) {
        fprintf(stderr, "name exceeds maximum length\n");
        return;
    }

    strncpy(chat->act_usrs[chat->usr_count++], username, MAX_USR_NAME);
}
