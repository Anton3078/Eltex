#include "../include/sig.h"

int
main () 
{
    sigset_t set;
    int ret;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    
    if ((ret = sigprocmask(SIG_BLOCK, &set, NULL)) < 0)
       errExit("sigprocmsk");
    
    printf("Start - %d\n", getpid());

    while (1) { 
        sleep(1);
    }

    exit(EXIT_SUCCESS);
}
