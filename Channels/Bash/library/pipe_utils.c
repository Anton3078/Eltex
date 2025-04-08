#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void
create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void
redirect_output (int pipefd[2]) 
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
}

void
redirect_input (int pipefd[2]) 
{
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
}

void
close_pipe (int pipefd[2]) 
{
    close(pipefd[0]);
    close(pipefd[1]);
}


