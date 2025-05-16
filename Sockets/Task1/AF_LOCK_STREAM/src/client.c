#include "../include/mysocket.h"

int
main ()
{
    unsigned char buf[BUF_SIZE];
    char *msg = "hello World!";
    int svSockFd;
    ssize_t numBytes;
    struct sockaddr_un svaddr;
    
    if ((svSockFd = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1)
       errExit("socket");

    memset(&svaddr, 0, sizeof(svaddr));

    svaddr.sun_family = AF_LOCAL;
    strncpy(svaddr.sun_path, MY_SOCK_PATH, sizeof(svaddr.sun_path) - 1);
    
    if (connect(svSockFd, (struct sockaddr *)&svaddr, sizeof(svaddr)) == -1)
       errExit("connect");

    send(svSockFd, msg, strlen(msg), 0);
    printf("Message sent: %s\n", msg);
    
    if ((numBytes = recv(svSockFd, buf, BUF_SIZE, 0)) == -1)
       errExit("recv");
    printf("Server response: %s\n", buf);
    
    if (close(svSockFd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);
}

