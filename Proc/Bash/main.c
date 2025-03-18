#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "mystring.h"

int
main(int argc, char* argv[]) {
    pid_t child_pid, stat;
    char *argVec[5];
    char command[30] = {0};

    while(1) {
        printf("@: ");

        MyStr(command);
        
        if (strncmp(command, "exit", 4) == 0) {
           break; 
        }

        get_tokens(argVec, command);
        
        if (strcmp(argVec[0], "cd") == 0) {
            if (argVec[1] == NULL) {
                if (chdir(".") != 0)
                        perror("cd");
            } else {
                if (chdir(argVec[1]) != 0)
                        perror("cd");

            }
            memset(command, 0, sizeof(command));
            memset(argVec, 0, sizeof(argVec));
            continue;
        }

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
                perror("execvp");
                exit(EXIT_FAILURE);
            default:
                wait(&stat);
                memset(command, 0, sizeof(command));
                memset(argVec, 0, sizeof(argVec));
        }
    
    }
}
