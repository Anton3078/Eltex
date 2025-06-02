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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define SERVER_PORT 7777
#define CLIENT_PORT 50020
#define BUF_SIZE 256
#define IPADDR_R "192.168.1.100"
#define IPADDR_S "192.168.1.101"
#define INDX_N "eth0"

#endif
