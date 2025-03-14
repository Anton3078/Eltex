#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void)
{
    pid_t child_pid, stat;

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
           printf("Chiled PID=%d PPID=%d\n", getpid(), getppid());
           exit(EXIT_SUCCESS);
       default:
           printf("Parent PID=%d PPID=%d\n", getpid(), getppid());
           wait(&stat);
           printf("Status exit of child %d\n", stat);
           exit(EXIT_SUCCESS);
   }
}

