#include "../include/mysocket.h"

extern int semid;

void
handler_serv(void *arg)
{
    struct ReqData *reqs = (struct ReqData *)arg;
    struct sembuf wait = {SEM_NOTIFY, -1, 0};
    struct sembuf lock = {SEM_ACCESS, -1, 0};
    struct sembuf unlock = {SEM_ACCESS, 1, 0};

    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");

    while (1) {
        semop(semid, &wait, 1);
        semop(semid, &lock, 1);

        if (reqs->ReqCount > 0) {
            struct request req = reqs->ReqHist[0];
            
            for (int i = 1; i < reqs->ReqCount; i++) {
                reqs->ReqHist[i - 1] = reqs->ReqHist[i];
            }
            reqs->ReqCount--;

            semop(semid, &unlock, 1);

            send_time(sock, &req.addr);
        } else {
            semop(semid, &unlock, 1);
        }
    }
}
