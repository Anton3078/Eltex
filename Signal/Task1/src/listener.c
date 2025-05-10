#include "../include/sig.h"

void 
signal_handler (int sig_n, siginfo_t *info, void *arg)
{
    int *parm = (int *) arg;
    printf("==============================================\n");
    printf("SIGUSR1 signal received\n");
    printf("Parametrs: %d\n", *parm);
    printf("Sender pid: %d\n", info->si_pid);
}

int
main () 
{
    struct sigaction act;
    sigset_t set;
    int ret;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    act.sa_sigaction = signal_handler;
    act.sa_mask = set;
    
    if ((ret = sigaction(SIGUSR1, &act, NULL)) < 0)
       errExit("sigaction");
    
    printf("Start - %d\n", getpid());

    while (1) { 
        sleep(1);
    }

    exit(EXIT_SUCCESS);
}
