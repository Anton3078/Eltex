#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "mystring.h"

int
main(int argc, char* argv[]) {
    pid_t child_pid;
    char *argVec[5];
    char command[30];

    while(1) {
        printf("@: ");

        MyStr(command);
        
        get_tokens(argVec, command);

        if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
            perror("signal");
            exit(EXIT_FAILURE);
        }
        child_pid = fork();

        switch (child_pid) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                execvp(argVec[0], argVec);

                exit(EXIT_FAILURE);
            default:
                wait(NULL);
                memset(command, 0, sizeof(command));
                memset(argVec, 0, sizeof(argVec));
        }
    
    }
}
