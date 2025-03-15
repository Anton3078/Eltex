#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void 
creat_proc(int count_inner_proc) {
    pid_t child_pid, stat;
    int i;

    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("Parent PID=%d PPID=%d\n", getpid(), getppid());
    printf("===========================================================\n"); 
    for (i = 0; i < count_inner_proc; ++i) {

        child_pid = fork();
        switch (child_pid) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                printf("Child PID=%d PPID=%d\n", getpid(), getppid());
                exit(EXIT_SUCCESS);
            default:
                wait(&stat);
                printf("Status exit of child %d\n", stat);
                printf("-----------------------------------------------------------\n");
        }

   }
   
   exit(EXIT_SUCCESS);
}
