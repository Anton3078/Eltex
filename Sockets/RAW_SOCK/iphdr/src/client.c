#include "../include/mysocket.h"

int 
main() 
{
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    int flag = 1;
    char *msg = "Hello World!";

    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0)
        errExit("socket");
    
    setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, IPADDR, &server_addr.sin_addr) <= 0)
        errExit("inet_pton");
    
    struct iphdr *ip_header = (struct iphdr *)buffer;
    ip_header->version = 4;
    ip_header->ihl = 5;
    ip_header->tos = 0;
    ip_header->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(msg));
    ip_header->id = htons(0);
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->check = 0;
    ip_header->saddr = 0;
    ip_header->daddr = server_addr.sin_addr.s_addr;

    struct udphdr *udp_header = (struct udphdr *)(buffer + sizeof(struct iphdr));
    udp_header->source = htons(CLIENT_PORT);
    udp_header->dest = htons(SERVER_PORT);
    udp_header->len = htons(sizeof(struct udphdr) + strlen(msg));
    udp_header->check = 0;

    char *data = buffer + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(data, msg);

    int packet_size = sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(msg);
    if (sendto(sockfd, buffer, packet_size, 0, (struct sockaddr *)&server_addr, addr_len) < 0)
        errExit("sendto");

    printf("Packet sent to server, waiting for response..\n");

    while (1) {
        if (recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len) < 0)
            errExit("recvfrom");

        struct udphdr *recv_udp = (struct udphdr *)(buffer + sizeof(struct iphdr));
        if (ntohs(recv_udp->dest) == CLIENT_PORT) {
            char *recv_data = buffer + sizeof(struct iphdr) + sizeof(struct udphdr);
            printf("Server response: %s\n", recv_data);
            break;
        }
    }

    close(sockfd);
    exit(EXIT_SUCCESS);
}
