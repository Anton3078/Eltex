#include "../include/shMemory.h"

void 
add_user(const char *username, struct DataChat *chat) 
{ /*  доабвление новых пользователей*/
    if (strlen(username) >= MAX_USR_NAME) {
        fprintf(stderr, "name exceeds maximum length\n");
        return;
    }

    strncpy(chat->act_usrs[chat->usr_count++], username, MAX_USR_NAME);
}
