#include "../include/mysocket.h"

int
main ()
{
    //unsigned char buf[BUF_SIZE];
    int sockFd;
    int flag = 1;
    char *msg = "Hello Client";
    struct sockaddr_in bcaddr;
    
    if ((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");

    if (setsockopt(sockFd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) == -1)
       errExit("setsockopt");
   
    memset(&bcaddr, 0, sizeof(bcaddr)); 
    bcaddr.sin_family = AF_INET;
    bcaddr.sin_port = htons(BROADCAST_PORT);
    if (inet_pton(AF_INET, BROADCAST_IP, &bcaddr.sin_addr) <= 0)
       errExit("inet_pton");

    //bcaddr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

    if (sendto(sockFd, msg, strlen(msg), 0, (struct sockaddr *)&bcaddr, sizeof(bcaddr)) == -1)
       errExit("sendto");

    if (close(sockFd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);


}
