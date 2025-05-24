#include "../../include/mysocket.h"

int 
main() 
{   
    int tcp_sockFd, tcp_clFd;
    int udp_sockFd;
    int epoll_fd;
    int nfds;
    struct epoll_event ev, events[MAX_EVENTS];
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
    
    if ((epoll_fd = epoll_create1(0)) == -1)
       errExit("epoll_create1");

    ev.events = EPOLLIN;
    ev.data.fd = tcp_sockFd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tcp_sockFd, &ev) == -1)
       errExit("epoll_ctl: tcp_sock");

    ev.data.fd = udp_sockFd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, udp_sockFd, &ev) == -1)
       errExit("epoll_ctl: udp_sock");

    printf("===Server is starting (epoll version)===\n");

    while (1) {
        if ((nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1)) == -1) {
           errExit("epoll_wait");
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == tcp_sockFd) {
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
            else if (events[n].data.fd == udp_sockFd) {
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
        }

        memset(buf, 0, sizeof(buf));
    }
    
    close(epoll_fd);    
    exit(EXIT_FAILURE);
}
