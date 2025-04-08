#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 10

int
main (int argc, char *argv[]) 
{
    int pipefd[2];
    char buf[BUF_SIZE];
    pid_t child_pid;
    ssize_t numRead;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();

    switch (child_pid) {
        case -1:
                perror("fork");
                exit(EXIT_FAILURE);
        
        case 0:
            
            if (close(pipefd[1]) == -1) {
               perror("close");
               exit(EXIT_FAILURE);
            }


            while ((numRead = read(pipefd[0], &buf, BUF_SIZE)) > 0) {
                    if(write(STDOUT_FILENO, buf, numRead) != numRead){
                        perror("write");
                        _exit(EXIT_FAILURE);
                    }
            }

            write(STDOUT_FILENO, "\n", 1);
            close(pipefd[0]);
            _exit(EXIT_SUCCESS);

            break;
        
        default:
            
            if (close(pipefd[0]) == -1) {
               perror("close");
               exit(EXIT_FAILURE);
            }

            if (write(pipefd[1], argv[1], strlen(argv[1])) != strlen(argv[1])) {
                    perror("write");
                    exit(EXIT_FAILURE);
            }

            if (close(pipefd[1]) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
            }

            wait(NULL);
            exit(EXIT_SUCCESS);
    }
}
