#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../fifo_header.h"
#include <unistd.h>
        
int 
main (int argc, char *argv[])
{
    int serverFd;
    char client_fifo[CLIENT_FIFO_LEN];

    
    if (mkfifo(SERVER_FIFO, 0664) == -1 && errno != EEXIST) {
        fprintf(stderr, "mkfifo %s\n", SERVER_FIFO);
        exit(EXIT_FAILURE);
    }
    
    serverFd = open(SERVER_FIFO, O_WRONLY);

    if (serverFd == -1) {
       fprintf(stderr, "open %s\n", CLIENT_FIFO);
       exit(EXIT_FAILURE);
    }

    if (write(serverFd, argv[1], strlen(argv[1])) != strlen(argv[1])) {
       fprintf(stderr, "Error writing to FIFO %s\n", client_fifo);
    }

    if (close(serverFd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

}
