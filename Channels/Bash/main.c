#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "pipe_utils.h"
#include "command_utils.h"
#include <sys/wait.h>


#define MAX_PIPE 10

int
main(void) {
    pid_t child_pid;
    char *commands[MAX_PIPE + 1] = {NULL};
    char command[MAX_COMMAND_LEN] = {0};
    char *argVec[MAX_ARGS] = {NULL};
    int pipefd1[2];
    int num_commands;
    int i;

    while(1) {
        printf_info();
        MyStr(command);
        
        if (strlen(command) == 0) continue;

        if (strcmp(command, "exit") == 0) break; 
        
        //Counting the number of pipes in command
        get_tokens(commands, command, "|");
        
        num_commands = 0;
        while(commands[num_commands]) num_commands++;

        if (strncmp(commands[0], "cd", 2) == 0) {
                get_tokens(argVec, commands[0], " ");
                execute_cd(argVec);
                continue;
        }
        

        for (i = 0; i < num_commands; ++i) {
            
            int pipefd2[2] = {-1, -1};
            if(i < num_commands - 1 && pipe(pipefd2) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }


            child_pid = fork();
            switch (child_pid) {
                case -1:
                    perror("fork");
                    exit(EXIT_FAILURE);
                case 0:
                    if (i > 0) { 
                       redirect_input(pipefd1);
                       close_pipe(pipefd1);
                    }

                    if (i < num_commands - 1) redirect_output(pipefd2);
                    
                    get_tokens(argVec, commands[i], " ");

                    if (argVec[0] == NULL) {
                       fprintf(stderr, "Empty command\n");
                      _exit(EXIT_FAILURE); 
                    }

                    execvp(argVec[0], argVec);
                    perror("execvp");
                    _exit(EXIT_FAILURE);

                default:
                    if (i > 0) close_pipe(pipefd1);
                    if (i < num_commands -1) {
                        pipefd1[0] = pipefd2[0];
                        pipefd1[1] = pipefd2[1];
                    }

                    waitpid(child_pid, NULL, 0);
            }
        }

        memset(command, 0, sizeof(command));
        memset(commands, 0, sizeof(commands));
        memset(argVec, 0, sizeof(argVec));
        
    }
    exit(EXIT_SUCCESS);
}
