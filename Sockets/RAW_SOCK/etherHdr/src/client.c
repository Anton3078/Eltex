#include "../include/mysocket.h"

int 
main() 
{
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_ll server_addr;
    int flag = 1;
    socklen_t addr_len = sizeof(server_addr);
    
    //MAC-address
    unsigned char src_mac[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    unsigned char dest_mac[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    
    char *msg = "Hello World!";
    int msg_len = strlen(msg);

    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
        errExit("socket");
    
    setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sll_family = AF_PACKET;
    server_addr.sll_ifindex = if_nametoindex(INDX_N);
    server_addr.sll_halen = ETH_ALEN;
    memcpy(server_addr.sll_addr, dest_mac, ETH_ALEN);
    
    // Ethernet header
    struct ethhdr *eth_header = (struct ethhdr *)buffer;
    memcpy(eth_header->h_dest, dest_mac, ETH_ALEN);
    memcpy(eth_header->h_source, src_mac, ETH_ALEN);
    eth_header->h_proto = htons(ETH_P_IP);
    
    //IP header
    struct iphdr *ip_header = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    ip_header->version = 4;
    ip_header->ihl = 5;
    ip_header->tos = 0;
    ip_header->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + msg_len);
    ip_header->id = htons(0);
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = IPPROTO_UDP;

    if (inet_pton(AF_INET, IPADDR_S, &ip_header->saddr) <= 0)
       errExit("inet_pton (sender addr)");
    
    if (inet_pton(AF_INET, IPADDR_R, &ip_header->daddr) <= 0)
        errExit("inet_pton (receiver addr)");

    //=culculating checksum=========================================
    ip_header->check = 0;
    unsigned short *ptr = (unsigned short *)ip_header;
    unsigned int csum = 0;

    for (int i = 0; i < 10; i++) {
        csum += ptr[i];
    }

    unsigned short tmp = csum >> 16;
    csum = (csum & 0xFFFF) + tmp;
    ip_header->check = ~(unsigned short)csum;
    //=========================================culculating checksum=
    
    // UDP header
    struct udphdr *udp_header = (struct udphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));
    udp_header->source = htons(CLIENT_PORT);
    udp_header->dest = htons(SERVER_PORT);
    udp_header->len = htons(sizeof(struct udphdr) + msg_len);
    udp_header->check = 0;

    char *data = buffer + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr);
    memcpy(data, msg, msg_len);

    int packet_size = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr) + msg_len;
    if (sendto(sockfd, buffer, packet_size, 0, (struct sockaddr *)&server_addr, addr_len) < 0)
        errExit("sendto");

    printf("Packet sent to server, waiting for response...\n");

    while (1) {
        if (recvfrom(sockfd, buffer, packet_size, 0, (struct sockaddr *)&server_addr, &addr_len) < 0)
            errExit("recvfrom");

        struct udphdr *recv_udp = (struct udphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));
        if (ntohs(recv_udp->dest) == CLIENT_PORT) {
            char *recv_data = buffer + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr);
            printf("Server response: %s\n", recv_data);
            break;
        }
    }

    close(sockfd);
    exit(EXIT_SUCCESS);
}
