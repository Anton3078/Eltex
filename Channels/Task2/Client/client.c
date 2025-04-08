#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../fifo_header.h"
#include <unistd.h>

int
main (void) 
{
    int clientFd;
    char client_fifo[CLIENT_FIFO_LEN];
    ssize_t numRead;

    clientFd = open(SERVER_FIFO, 0664);

    if (clientFd == -1) {
        fprintf(stderr, "open %s\n", SERVER_FIFO);
        exit(EXIT_FAILURE);
    }

    while ((numRead = read(clientFd, client_fifo, CLIENT_FIFO_LEN)) > 0) {
        if (write(STDOUT_FILENO, client_fifo, numRead) != numRead) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (write(STDOUT_FILENO, "\n", 1) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    
    if (close(clientFd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
