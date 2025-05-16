#include "../include/mysocket.h"

int
main ()
{
    unsigned char buf[BUF_SIZE];
    int sockfd, clfd;
    ssize_t numBytes;
    struct sockaddr_un svaddr, claddr;
    socklen_t addr_size;
    
    if ((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1)
       errExit("socket");

    if (remove(MY_SOCK_PATH) == -1)
       errExit("remove");
    
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sun_family = AF_LOCAL;
    strncpy(svaddr.sun_path, MY_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

    if (bind(sockfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) == -1)
       errExit("bind");

    if (listen(sockfd, 5) == -1)
       errExit("listen");

    addr_size = sizeof(claddr);
    if ((clfd = accept(sockfd, (struct sockaddr *)&claddr, &addr_size)) == -1)
       errExit("accept");

    if ((numBytes = recv(clfd, buf, BUF_SIZE, 0)) == -1)
       errExit("recv");
    
    printf("Message received from client: %s\n", buf);
    buf[0] = toupper((unsigned char) buf[0]);
    send(clfd, buf, BUF_SIZE, 0);
    printf("sent: %s\n", buf);
    
    if (close(clfd) == -1)
       errExit("close");

    if (close(sockfd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);
}
