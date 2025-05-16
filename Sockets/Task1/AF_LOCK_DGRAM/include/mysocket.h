#ifndef SOCK_H
#define SOCK_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/un.h>
#include <unistd.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define MY_SOCK_PATH "/tmp/my_sock_path"
#define CLIENT_SOCK_PATH "/tmp/client_sock_path"
#define BUF_SIZE 32

#endif
