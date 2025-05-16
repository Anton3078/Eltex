#include "../include/mysocket.h"

int
main ()
{
    struct sockaddr_un svaddr, claddr;
    int sockFd;
    char *msg = "hello world!";
    unsigned char buf[BUF_SIZE];
    ssize_t numBytes;
    
    if ((sockFd = socket(AF_LOCAL, SOCK_DGRAM, 0)) == -1)
       errExit("socket");

    memset(&claddr, 0, sizeof(claddr));
    claddr.sun_family = AF_LOCAL;
    strncpy(claddr.sun_path, CLIENT_SOCK_PATH, sizeof(claddr.sun_path) - 1);
    
    if (bind(sockFd, (struct sockaddr *) &claddr, sizeof(struct sockaddr_un)) == -1)
       errExit("bind");
    
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sun_family = AF_LOCAL;
    strncpy(svaddr.sun_path, MY_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

    sendto(sockFd, msg, strlen(msg), 0, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un));
    printf("Message sent: %s\n", msg);
    
    if ((numBytes = recvfrom(sockFd, buf, BUF_SIZE, 0, NULL, NULL)) == -1)
       errExit("recv");
    printf("Server response: %s\n", buf);
    
    remove(claddr.sun_path);

    if (close(sockFd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);
}

