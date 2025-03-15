#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "print_pid.h"

int
main(void)
{
    pid_t child_pid, stat;
    int count_chld;
    int i;

    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
       perror("signal");
       exit(EXIT_FAILURE);
    }
   
    printf("Parent PID=%d PPID=%d\n", getpid(), getppid());
    printf("========================================================\n");

    for (i = 0; i < 2; ++i) {
        
        printf("Enter: the count of child proc: ");
        scanf("%d", &count_chld);

        child_pid = fork();
   
        switch (child_pid) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                /*printf("Child PID=%d PPID=%d\n", getpid(), getppid());
                exit(EXIT_SUCCESS);*/
                creat_proc(count_chld);
            default:
                wait(&stat);
                printf("Parent status exit %d\n", stat);
                printf("-----------------------------------------------------------\n");
        }

   }
   
   exit(EXIT_SUCCESS);
}

