#include "../include/mysocket.h"

int
main ()
{
    int sockFd;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];
    socklen_t size_addr;

    if ((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(BROADCAST_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockFd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
       errExit("bind");

    size_addr = sizeof(addr);
    if (recvfrom(sockFd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &size_addr) < 0)
       errExit("recvfrom");
    
    printf("Broadcast message from sender: %s\n", buf);

    if (close(sockFd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);
                    
}
