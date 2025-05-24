#include "../../include/mysocket.h"

int 
main() 
{   
    int tcp_sockFd, tcp_clFd;
    int udp_sockFd;
    struct pollfd fds[2];
    struct sockaddr_in svaddr, claddr;
    socklen_t addr_size = sizeof(claddr);
    unsigned char buf[BUF_SIZE];
    
    // TCP
    if ((tcp_sockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
       errExit("socket (tcp)");
    
    // UDP
    if ((udp_sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket (udp)");

    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &svaddr.sin_addr) <= 0)
       errExit("inet_pton");
    
    // TCP
    if (bind(tcp_sockFd, (struct sockaddr *)&svaddr, sizeof(svaddr)) == -1)
       errExit("bind (tcp)");

    // UDP
    if (bind(udp_sockFd, (struct sockaddr *)&svaddr, sizeof(svaddr)) == -1)
       errExit("bind (udp)");

    if (listen(tcp_sockFd, 5) == -1)
       errExit("listen");
    
    fds[0].fd = tcp_sockFd;
    fds[0].events = POLLIN;
    fds[1].fd = udp_sockFd;
    fds[1].events = POLLIN;

    printf("===Server is starting (poll version)===\n");

    while (1) {
        if (poll(fds, 2, -1) == -1) {
           errExit("poll");
        }

        if (fds[0].revents & POLLIN) {
           if ((tcp_clFd = accept(tcp_sockFd, (struct sockaddr *)&claddr, &addr_size)) == -1)
              errExit("accept");

           if (recv(tcp_clFd, buf, BUF_SIZE, 0) == -1)
              errExit("recv (tcp)");
           
           struct con_addr connection;
           connection.proto = TCP;
           connection.sockFd = tcp_clFd;

           printf("====================================================================\n");
           printf("Message received from TCP client: %s\n", buf);

           send_time(&connection);
           
           if (close(tcp_clFd) == -1)
              errExit("close");

           printf("Send current time success\n"); 
        }
        else if (fds[1].revents & POLLIN) {
           if (recvfrom(udp_sockFd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &addr_size) == -1)
              errExit("recvfrom");
           
           struct con_addr connection;
           connection.proto = UDP;
           connection.sockFd = udp_sockFd;
           connection.addr = (struct sockaddr *)&claddr;
           connection.addr_size = addr_size;
           
           printf("====================================================================\n");
           printf("Message received from UDP client: %s\n", buf);
           
           send_time(&connection);
           printf("Send current time success\n"); 
        }

        memset(buf, 0, sizeof(buf));
    }
    exit(EXIT_SUCCESS);
}
