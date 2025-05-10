#include "../include/sig.h"

int 
main (int argc, char *argv[]) 
{   
    pid_t pid;

    if (argc < 2)
       errExit("few arguments");
    
    pid = atoi(argv[1]);
    printf("Send SIGINT signal to %d\n", pid);
    kill(pid, SIGINT);

    exit(EXIT_SUCCESS);

}
