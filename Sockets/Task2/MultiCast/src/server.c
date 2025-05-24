#include "../include/mysocket.h"

int
main ()
{
    int sockFd;
    char *msg = "Hello Client";
    struct sockaddr_in mul_addr;
    
    if ((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");
    
    memset(&mul_addr, 0, sizeof(mul_addr));
    mul_addr.sin_family = AF_INET;
    mul_addr.sin_port = htons(MULTICAST_PORT);
    if (inet_pton(AF_INET, MULTICAST_GROUP, &mul_addr.sin_addr) <= 0)
       errExit("inet_pton");

    if (sendto(sockFd, msg, strlen(msg), 0, (struct sockaddr *)&mul_addr, sizeof(mul_addr)) == -1)
       errExit("sendto");

    if (close(sockFd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);


}
