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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define BUF_SIZE 32
#define MULTICAST_GROUP "239.255.42.42"
#define MULTICAST_PORT 50002

#endif
