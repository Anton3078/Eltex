#include "../include/mysocket.h"

int
main ()
{
    unsigned char buf[BUF_SIZE];

    int sockfd, clfd;
    ssize_t numBytes;
    struct sockaddr_in svaddr, claddr;
    socklen_t addr_size;
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
       errExit("socket");
    
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, "127.0.0.1", &svaddr.sin_addr) <= 0)
       errExit("inet_pton");
    
    if (bind(sockfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_in)) == -1)
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
