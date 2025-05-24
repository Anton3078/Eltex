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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define PORT 50002
#define MAX_CLIENT 2
#define BUF_SIZE 256
#define MAX_SERVER 4
#define PATH_KEY_SHM "/tmp"
#define PROJ_SHM_ID 1
#define PATH_KEY_SEM "/tmp"
#define PROJ_SEM_ID 2
#define SEM_ACCESS 0
#define SEM_NOTIFY 1

extern int semid;  

struct request {
    struct sockaddr_in addr; 
    char rtext[BUF_SIZE];
};

struct ReqData {
    struct request ReqHist[MAX_SERVER + 5];
    int ReqCount;
};

void send_time(int sock, struct sockaddr_in *addr);
void handler_serv(void *arg);

#endif
