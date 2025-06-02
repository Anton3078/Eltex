#include "../include/mysocket.h"

int
main ()
{
    unsigned char buf[BUF_SIZE];
    int sockfd;
    ssize_t numBytes;
    struct sockaddr_in svaddr, claddr;
    socklen_t claddr_size;
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");
    
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(SERVER_PORT);
    
    if (inet_pton(AF_INET, IPADDR, &svaddr.sin_addr) <= 0)
       errExit("inet_pton");
    
    if (bind(sockfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_in)) == -1)
       errExit("bind");

    claddr_size = sizeof(claddr);
    
    if ((numBytes = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &claddr_size)) < 0)
       errExit("recv");
        
    printf("Message received from client: %s\n", buf);

    buf[0] = '1';
    buf[1] = '2';
    sendto(sockfd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, claddr_size);
    printf("sent: %s\n", buf);
    
    if (close(sockfd) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);
}
