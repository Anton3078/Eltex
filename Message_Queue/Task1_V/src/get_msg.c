#include "../include/msg_queue.h"
#include <string.h>

void
get_msg (int qid, int msgtype) 
{
    struct MsgBuf msg;

    if (msgrcv(qid, &msg, sizeof(msg.mtext), msgtype, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    } else {
        printf("%s\n", msg.mtext);
    }
}
