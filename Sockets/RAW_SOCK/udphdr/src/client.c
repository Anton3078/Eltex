#include "../include/mysocket.h"

int 
main() 
{
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    
    char *msg = "Hello World!";

    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0)
        errExit("socket");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, IPADDR, &server_addr.sin_addr) <= 0)
        errExit("inet_pton");

    struct udphdr *udp_header = (struct udphdr *)buffer;
    udp_header->source = htons(CLIENT_PORT);
    udp_header->dest = htons(SERVER_PORT);
    udp_header->len = htons(sizeof(struct udphdr) + strlen(msg)); 
    udp_header->check = 0;

    char *data = buffer + sizeof(struct udphdr);
    strcpy(data, msg);

    if (sendto(sockfd, buffer, sizeof(struct udphdr) + strlen(msg), 0, (struct sockaddr *)&server_addr, addr_len) < 0)
        errExit("sendto");
    
    printf("Packet sent to server, waiting for response..\n");

    while (1) {
        if (recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len) < 0)
            errExit("recvfrom");

        struct udphdr *recv_udp = (struct udphdr *)(buffer + 20);
        if (ntohs(recv_udp->dest) == CLIENT_PORT) {
            char *recv_data = buffer + sizeof(recv_udp + 1);
            printf("Server response: %s\n", recv_data + 20);
            break;
        }
    }

    close(sockfd);
    exit(EXIT_SUCCESS);
}
