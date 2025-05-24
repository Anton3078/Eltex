#include "../include/mysocket.h"

void *
send_time (void *argv)
{
    int clFd = *((int *)argv);
    time_t tim;
    struct tm *timeinfo;
    char buf[80];
    
    time(&tim);
    timeinfo = localtime(&tim);
    
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    send(clFd, buf, strlen(buf), 0);
    printf("Executing server for client %d (Thread ID: %lu)\n", clFd, pthread_self());    
    fflush(stdout);
    
    free(argv);
    close(clFd);
    pthread_exit(NULL);
}
