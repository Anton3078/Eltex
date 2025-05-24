#include "../include/mysocket.h"

void
send_time (int clFd)
{
    time_t tim;
    struct tm *timeinfo;
    char buf[80];
    
    time(&tim);
    timeinfo = localtime(&tim);
    
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    send(clFd, buf, strlen(buf) + 1, 0);
    
    printf("Executing server for client %d (Thread ID: %lu)\n", clFd, pthread_self());    
    //fflush(stdout);
    
    //if (close(clFd) == -1)
    //   errExit("close");
}
