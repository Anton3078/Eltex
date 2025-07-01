#ifndef SOCK_H
#define SOCK_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)

#define MAX_MSG 512

#define MAX_CLIENTS 2
#define MAX_SERVER 4

#define SEM_ACCESS 0
#define SEM_NOTIFY 1

#define PATH_KEY_SHM "/tmp"
#define PROJ_SHM_ID 1
#define PATH_KEY_SEM "/tmp"
#define PROJ_SEM_ID 2

extern int semid;

struct client_data {
    uint32_t ip;
    uint16_t port;
    unsigned int counter;
};

struct Messg {
    struct sockaddr_ll s_addr;
    char mtext[MAX_MSG];
};

#pragma pack(push, 1)
struct packet {
    struct ethhdr eth;
    struct iphdr ip;
    struct udphdr udp;
    struct Messg payload;
};
#pragma pack(pop)

struct data_transfer {
    struct packet pk_hist[MAX_SERVER];
    unsigned int pk_count;
    struct client_data clients[MAX_CLIENTS];
    unsigned int cli_count;
};

unsigned short checksum(struct iphdr *);

void swap_mac_address(struct packet *);
void swap_ip_address(struct packet *);
void swap_udp_ports(struct packet *);

int find_client(struct data_transfer *, uint32_t, uint16_t);
void add_client(struct data_transfer *, uint32_t, uint16_t);
void reset_client(struct data_transfer *, uint32_t, uint16_t);

int get_interface_mac(const char *, unsigned char *);

void handler_serv(struct data_transfer *);

void pr_pkt_info(const struct packet *pkt);
#endif

