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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define SERVER_PORT 7777
#define CLIENT_PORT 50020
#define BUF_SIZE 256
#define IPADDR "127.0.0.1"

#endif
