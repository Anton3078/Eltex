#include "../include/mysocket.h"

int
main ()
{
    struct sockaddr_un svaddr, claddr;
    int sockFd;
    ssize_t numBytes;
    socklen_t len;
    unsigned char buf[BUF_SIZE];
    
    if ((sockFd = socket(AF_LOCAL, SOCK_DGRAM, 0)) == -1)
       errExit("socket");

    if (remove(MY_SOCK_PATH) == -1)
       errExit("remove");
    
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sun_family = AF_LOCAL;
    strncpy(svaddr.sun_path, MY_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

    if (bind(sockFd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) == -1)
       errExit("bind");

    len = sizeof(claddr);
    if ((numBytes = recvfrom(sockFd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &len)) == -1)
       errExit("recv");
    printf("Message received from client: %s\n", buf);

    buf[0] = toupper((unsigned char) buf[0]);
    sendto(sockFd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, len);
    printf("sent: %s\n", buf);

    if (close(sockFd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);
}
