#include "../../include/mysocket.h"

int
main ()
{   
    int tcp_sockFd, tcp_clFd;
    int udp_sockFd;
    fd_set readfds;
    int max_fd = -1;
    struct sockaddr_in svaddr, claddr;
    int ret;
    socklen_t addr_size = sizeof(claddr);
    unsigned char buf[BUF_SIZE];
    
    // TCP
    if ((tcp_sockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
       errExit("socket (tcp)");
    
    // UDP
    if ((udp_sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
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
    
    printf("===Server is starting===\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(tcp_sockFd, &readfds);
        FD_SET(udp_sockFd, &readfds);
        
        max_fd = (tcp_sockFd > udp_sockFd) ? tcp_sockFd : udp_sockFd;

        if ((ret = select(max_fd + 1, &readfds, NULL, NULL, NULL)) == -1) {
           errExit("select");
        } 

        if (FD_ISSET(tcp_sockFd, &readfds) != 0) {
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
           
           FD_CLR(tcp_clFd, &readfds);

           if (close(tcp_clFd) == -1)
              errExit("close");

           printf("Send current time success\n"); 
        }
        else if (FD_ISSET(udp_sockFd, &readfds) != 0) {
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

