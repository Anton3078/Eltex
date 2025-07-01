#include "../include/mysocket.h"

void 
pr_pkt_info(const struct packet *pkt) {
    char src_ip[INET_ADDRSTRLEN];
    char dst_ip[INET_ADDRSTRLEN];
    char src_mac[18];
    char dst_mac[18];
    
    snprintf(src_mac, sizeof(src_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
             pkt->eth.h_source[0], pkt->eth.h_source[1], pkt->eth.h_source[2],
             pkt->eth.h_source[3], pkt->eth.h_source[4], pkt->eth.h_source[5]);
    
    snprintf(dst_mac, sizeof(dst_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
             pkt->eth.h_dest[0], pkt->eth.h_dest[1], pkt->eth.h_dest[2],
             pkt->eth.h_dest[3], pkt->eth.h_dest[4], pkt->eth.h_dest[5]);

    inet_ntop(AF_INET, &(pkt->ip.saddr), src_ip, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(pkt->ip.daddr), dst_ip, INET_ADDRSTRLEN);
    
    printf("===== Packet =====\n");

    printf("\n=== Ethernet Header ===\n");
    printf("Source MAC: %s\n", src_mac);
    printf("Destination MAC: %s\n", dst_mac);
    printf("Ethertype: 0x%04x\n", ntohs(pkt->eth.h_proto));

    printf("\n=== IP Header ===\n");
    printf("Version: %d\n", pkt->ip.version);
    printf("Header Length: %d bytes\n", pkt->ip.ihl * 4);
    printf("Type of Service: %d\n", pkt->ip.tos);
    printf("Total Length: %d bytes\n", ntohs(pkt->ip.tot_len));
    printf("Identification: %d\n", ntohs(pkt->ip.id));
    printf("TTL: %d\n", pkt->ip.ttl);
    printf("Protocol: %d\n", pkt->ip.protocol);
    printf("Checksum: 0x%04x\n", ntohs(pkt->ip.check));
    printf("Source IP: %s\n", src_ip);
    printf("Destination IP: %s\n", dst_ip);

    printf("\n=== UDP Header ===\n");
    printf("Source Port: %d\n", ntohs(pkt->udp.source));
    printf("Destination Port: %d\n", ntohs(pkt->udp.dest));
    printf("Length: %d bytes\n", ntohs(pkt->udp.len));
    printf("Checksum: 0x%04x\n", ntohs(pkt->udp.check));

    printf("\n=== Payload ===\n");
    printf("Length: %zu bytes\n", strlen(pkt->payload.mtext));
    printf("Content: \"%s\"\n", pkt->payload.mtext);
    
    printf("==============================\n");
}

unsigned short
checksum(struct iphdr *ip_header)
{
    unsigned short *ptr = (unsigned short *)ip_header;
    unsigned int csum = 0;
    
    for (int i = 0; i < 10; i++) {
        csum += ptr[i];
    }

    unsigned short tmp = csum >> 16;
    csum = (csum & 0xFFFF) + tmp;
    return ~(unsigned short)csum;
}

void 
swap_mac_address(struct packet *pkt) 
{
    unsigned char tmp_mac[ETH_ALEN];
    memcpy(tmp_mac, pkt->eth.h_dest, ETH_ALEN);
    memcpy(pkt->eth.h_dest, pkt->eth.h_source, ETH_ALEN);
    memcpy(pkt->eth.h_source, tmp_mac, ETH_ALEN);
}

void 
swap_ip_address(struct packet *pkt) 
{
    uint32_t tmp_ip = pkt->ip.daddr;
    pkt->ip.daddr = pkt->ip.saddr;
    pkt->ip.saddr = tmp_ip;
}

void 
swap_udp_ports(struct packet *pkt) 
{
    uint16_t tmp_port = pkt->udp.dest;
    pkt->udp.dest = pkt->udp.source;
    pkt->udp.source = tmp_port;
}

int 
find_client(struct data_transfer *data, uint32_t ip, uint16_t port) 
{
    for (int i = 0; i < data->cli_count; i++) {
        if (data->clients[i].ip == ip && data->clients[i].port == port) {
            return i;
        }
    }
    return -1;
}

void 
add_client(struct data_transfer *data , uint32_t ip, uint16_t port) 
{
    if (data->cli_count >= MAX_CLIENTS) return;
    
    data->clients[data->cli_count].ip = ip;
    data->clients[data->cli_count].port = port;
    data->clients[data->cli_count].counter = 0;
    data->cli_count++;
}

void 
reset_client(struct data_transfer *data, uint32_t ip, uint16_t port) 
{
    int index = find_client(data, ip, port);
    if (index == -1) return;
    
    data->clients[index].counter = 0;
}

int 
get_interface_mac(const char *interface, unsigned char *mac) 
{
    struct ifreq ifr;
    int sock;
    
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    strncpy(ifr.ifr_name, interface, IFNAMSIZ);
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl");
        close(sock);
        return -1;
    }

    memcpy(mac, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
    close(sock);
    return 0;
}

