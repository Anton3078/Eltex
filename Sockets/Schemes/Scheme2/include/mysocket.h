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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define PORT 50002
#define MAX_CLIENT 2
#define BUF_SIZE 256
#define MAX_THREADS 4

struct ExeServ {
    pthread_t thread;
    int clFd;
    unsigned short isBusy;
};


void send_time(int);
void *handler_serv (void *);

#endif
