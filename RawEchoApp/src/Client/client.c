#include "../../include/mysocket.h"

int 
main(int argc, char *argv[]) 
{
    if (argc != 7) 
        errExit("Usage: ./client <client_ip> <client_port> <server_ip> <server_port> <interface> <server_mac>");
    
    int sockfd;
    struct sockaddr_ll svaddr;

    struct packet pkt;
    memset(&pkt, 0, sizeof(struct packet));    

    char *cli_ip_addr = argv[1];
    unsigned int cli_port = atoi(argv[2]);
    char *serv_ip_addr = argv[3];
    unsigned int serv_port = atoi(argv[4]);
    char *interface = argv[5];
    

    unsigned char dest_mac[ETH_ALEN];
    if (sscanf(argv[6], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
       &dest_mac[0], &dest_mac[1], &dest_mac[2],
       &dest_mac[3], &dest_mac[4], &dest_mac[5]) != 6)
         errExit("Invalid server MAC");
    unsigned char src_mac[ETH_ALEN];
    if (get_interface_mac(interface, src_mac) != 0) {
        errExit("Invalid client MAC");
    }
    //=create & setting socket==========================================
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
       errExit("socket");
    
    
    svaddr.sll_family = AF_PACKET;
    svaddr.sll_ifindex = if_nametoindex(interface);
    svaddr.sll_halen = ETH_ALEN;
    memcpy(svaddr.sll_addr, dest_mac, ETH_ALEN);

    // Ethernet header
    struct ethhdr *eth_header = &pkt.eth;
    memcpy(eth_header->h_dest, dest_mac, ETH_ALEN);
    memcpy(eth_header->h_source, src_mac, ETH_ALEN);
    eth_header->h_proto = htons(ETH_P_IP);
    
    //IP header
    struct iphdr *ip_header = &pkt.ip;
    ip_header->version = 4;
    ip_header->ihl = 5;
    ip_header->tos = 0;
    ip_header->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(struct Messg));
    ip_header->id = htons(0);
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = IPPROTO_UDP;

    if (inet_pton(AF_INET, cli_ip_addr, &ip_header->saddr) <= 0)
       errExit("inet_pton (sender addr)");
    
    if (inet_pton(AF_INET, serv_ip_addr, &ip_header->daddr) <= 0)
        errExit("inet_pton (receiver addr)");

    //=culculating checksum=========================================
    ip_header->check = 0;
    ip_header->check = checksum(ip_header);
    //=========================================culculating checksum=
    
    // UDP header
    struct udphdr *udp_header = &pkt.udp;
    udp_header->source = htons(cli_port);
    udp_header->dest = htons(serv_port);
    udp_header->len = htons(sizeof(struct udphdr) + sizeof(struct Messg));
    udp_header->check = 0;
    //======================================================create & setting socket=

    struct Messg *data = &pkt.payload;
    printf("====Start Client ====\n");
    while (1) {
        char input[MAX_MSG];
        printf("$: ");
        if (!fgets(input, MAX_MSG, stdin)) break;
        input[strcspn(input, "\n")] = 0;
        strncpy(data->mtext, input, MAX_MSG - 1);
        data->mtext[MAX_MSG - 1] = '\0';

        if (sendto(sockfd, &pkt, sizeof(struct packet), 0, (struct sockaddr *)&svaddr, sizeof(svaddr)) < 0)
            errExit("sendto");
        
        if (memcmp(input, "exit", 4) == 0) break;
        
        while (1) {
            struct sockaddr_ll serv_addr;
            struct packet recv_pkt;
            socklen_t addr_len_s = sizeof(serv_addr);
            if (recvfrom(sockfd, &recv_pkt, sizeof(struct packet), 0, (struct sockaddr *)&serv_addr, &addr_len_s) == -1)
                errExit("recvfrom");

            struct udphdr *recv_udp = (struct udphdr *)&recv_pkt.udp;
            if(ntohs(recv_udp->dest) == cli_port && ntohs(recv_udp->source) == serv_port) {
                printf("Server: %s\n", recv_pkt.payload.mtext);
                break;
            }
        
        }
    }
    
    if (close(sockfd) == -1)
       errExit("close");
    exit(EXIT_SUCCESS);
}

