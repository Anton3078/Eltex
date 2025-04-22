#include "../include/msg_queue.h"

void 
add_user(const char *username, char users[MAX_USR][MAX_USR_NAME], int *usr_count) 
{
    /*
    if (*usr_count >= MAX_USR) {
        fprintf(stderr, "User limit reached\n");
        return;
    }

    for (int i = 0; i < *usr_count; i++) {
        if (strcmp(users[i], username) == 0) {
            fprintf(stderr, "User already exists\n");
            return;
        }
    }
    */
    strncpy(users[*usr_count], username, MAX_USR_NAME);
    (*usr_count)++;
}
