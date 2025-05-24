#include "../include/mysocket.h"

extern pthread_mutex_t mtx;
extern pthread_cond_t cond;

void *
handler_serv (void *arg)
{
    struct ExeServ *server = (struct ExeServ *)arg;
    while (1) {
        pthread_mutex_lock(&mtx);
        
        while (server->isBusy == 0) {
            pthread_cond_wait(&cond, &mtx);
        }
        
        int cur_fd = server->clFd;        
        pthread_mutex_unlock(&mtx);

        if (cur_fd != -1)
           send_time(cur_fd);

        pthread_mutex_lock(&mtx);
        server->isBusy = 0;
        if (close(server->clFd) == -1)
           errExit("clsoe");
        server->clFd = -1;
        

        pthread_mutex_unlock(&mtx);
    }
}
