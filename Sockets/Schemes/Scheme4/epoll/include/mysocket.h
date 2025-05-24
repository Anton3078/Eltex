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
#include <pthread.h>
#include <malloc.h>
#include <sys/epoll.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define PORT 50002
#define MAX_CLIENT 2
#define MAX_EVENTS 8
#define BUF_SIZE 256

enum con_proto {
    TCP = 0,
    UDP = 1
};

struct con_addr {
    enum con_proto proto;
    int sockFd;
    struct sockaddr *addr;
    socklen_t addr_size;
};

void send_time(struct con_addr *);

#endif
