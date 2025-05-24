#include "../include/mysocket.h"

int
main ()
{
    int sockFd;
    struct sockaddr_in addr;
    struct ip_mreqn mreq;
    char buf[BUF_SIZE];
    socklen_t size_addr;

    if ((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");
    
    memset(&addr, 0, sizeof(addr)); 
    addr.sin_family = AF_INET;
    addr.sin_port = htons(MULTICAST_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockFd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
       errExit("bind");
    
    memset(&mreq, 0, sizeof(mreq));
    if (inet_pton(AF_INET, MULTICAST_GROUP, &mreq.imr_multiaddr.s_addr) <= 0)
       errExit("inet_pton (multiaddr)");
    mreq.imr_address.s_addr = INADDR_ANY;

    if (setsockopt(sockFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) == -1)
       errExit("setsockopt");
    
    size_addr = sizeof(addr);
    if (recvfrom(sockFd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &size_addr) < 0)
       errExit("recvfrom");
    
    printf("Multicast message from sender: %s\n", buf);

    if (close(sockFd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);
                    
}
