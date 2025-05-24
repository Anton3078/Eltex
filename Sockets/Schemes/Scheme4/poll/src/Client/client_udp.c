#include "../include/mysocket.h"

int
main ()
{
    unsigned char buf[BUF_SIZE];
    char *msg = "hello World!";
    int svSockFd;
    ssize_t numBytes;
    struct sockaddr_in svaddr;
    
    if ((svSockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");

    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, "127.0.0.1", &svaddr.sin_addr) <= 0)
       errExit("inet_pton");
    
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

