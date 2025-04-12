#include <string.h>
#include "../include/msg_queue.h"

void
send_msg(int qid, struct MsgBuf *msg)  
{
    if (msgsnd(qid, msg, sizeof(msg->mtext), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
}
