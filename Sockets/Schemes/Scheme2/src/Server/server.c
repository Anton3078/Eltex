#include "../../include/mysocket.h"

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int
main ()
{    
    int sockFd, client_fd;
    struct sockaddr_in svaddr;
    int flag = 1;
    int iter = 0;
    socklen_t addr_size = sizeof(svaddr);
    struct ExeServ servers[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; ++i) {
        servers[i].isBusy = 0;
        servers[i].clFd = -1;
        pthread_create(&servers[i].thread, NULL, handler_serv, &servers[i]);
    }

    if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
       errExit("socket");
    
    if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1)
       errExit("setsockopt");

    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &svaddr.sin_addr) <= 0)
       errExit("inet_pton");

    if (bind(sockFd, (struct sockaddr *)&svaddr, sizeof(svaddr)) == -1)
       errExit("bind");

    if (listen(sockFd, 5) == -1)
       errExit("listen");

    while (1) {
        
       if ((client_fd = accept(sockFd, (struct sockaddr *)&svaddr, &addr_size)) == -1)
          errExit("accept");
       

       pthread_mutex_lock(&mtx);
       printf("= Iteration #%d ==================================================\n", iter);
       for (int i = 0; i < MAX_THREADS; ++i) {
           if (servers[i].isBusy == 0) {
              servers[i].clFd = client_fd;
              servers[i].isBusy = 1;
              pthread_cond_broadcast(&cond);
              break;
           }
       }
       iter++;

       pthread_mutex_unlock(&mtx);
    }
    
    exit(EXIT_FAILURE);
}

