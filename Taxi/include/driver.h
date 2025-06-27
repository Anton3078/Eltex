#ifndef DRIVER_CORE_H
#define DRIVER_CORE_H

#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>

#define MAX_EVENTS 4
#define MAX_MSG 64
#define MAX_DRIVERS 4
#define errExit(msg) do { perror(msg); break; } while(0)
#define error(msg) do { perror(msg); continue; } while(0)
#define PIP_WR 1 
#define PIP_RD 0

enum CMD_TYPE {
    SND_TSK,
    GET_STAT,
};

enum Driver_status {
    AVAILABLE,
    BUSY
};

struct driver {
    pid_t pid;
    enum Driver_status stat;
    timer_t timer;
    int pip[2];
    int pip_cli[2];
};

struct command {
    enum CMD_TYPE type;
    pid_t pid;
    int timer;
};

void handle_driver(struct driver *);
int send_command(struct driver *, int *, struct command *);
int get_response(struct driver *, int *, struct command *);

#endif
