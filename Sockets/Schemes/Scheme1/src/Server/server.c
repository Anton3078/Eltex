#include "../../include/mysocket.h"

int
main ()
{   
    int sockFd, clFd;
    struct sockaddr_in svaddr;
    int flag = 1;
    socklen_t addr_size = sizeof(svaddr);

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
        
       if ((clFd = accept(sockFd, (struct sockaddr *)&svaddr, &addr_size)) == -1)
          errExit("accept");
       
       int *client_fd = malloc(sizeof(int));
       *client_fd = clFd;     

       pthread_t thread;
       pthread_create(&thread, NULL, send_time, (void *)client_fd);
       pthread_detach(thread);
    }
    
    exit(EXIT_FAILURE);
}

