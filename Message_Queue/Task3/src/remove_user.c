#include "../include/msg_queue.h"

void 
remove_user(const char *username, char users[MAX_USR][MAX_USR_NAME], int *usr_count) 
{
    for (int i = 0; i < *usr_count; ++i) {
        if (strcmp(users[i], username) == 0) {
            for (int j = i; j < *usr_count - 1; ++j) {
                strcpy(users[j], users[j + 1]);
            }
            (*usr_count)--;
            return;
        }
    }
}
