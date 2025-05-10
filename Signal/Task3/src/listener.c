#include "../include/sig.h"

int
main () 
{
    sigset_t set;
    int ret;
    int sig_n;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    if ((ret = sigprocmask(SIG_BLOCK, &set, NULL)) < 0)
       errExit("sigprocmask");
    
    printf("Start - %d\n", getpid());

    while (1) { 
        sigwait(&set, &sig_n);
        printf("Received signal %d\n", sig_n);
    }

    exit(EXIT_SUCCESS);
}
