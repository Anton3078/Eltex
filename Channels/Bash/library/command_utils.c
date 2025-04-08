#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void
execute_cd (char **args) 
{
    char *dir = args[1];
    if (dir == NULL) {
        dir = ".";
        if (dir == NULL) {
            fprintf(stderr, "cd: current not set\n");
        }
    }
    if (chdir(dir) != 0) {
        perror("cd");
    }
    
}

void
execute_command (char **args)
{
    pid_t pid = fork();

    switch (pid) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            execvp(args[0], args);
            perror("execvp");
            _exit(EXIT_FAILURE);

        default:
            waitpid(pid, NULL, 0);
    }
}

