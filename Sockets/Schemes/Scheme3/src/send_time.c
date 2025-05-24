#include "../include/mysocket.h"

void
send_time(int sock, struct sockaddr_in *addr)
{
    time_t tim;
    struct tm *timeinfo;
    char buf[80];
    
    time(&tim);
    timeinfo = localtime(&tim);
    
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    sendto(sock, buf, strlen(buf) + 1, 0, (struct sockaddr *)addr, sizeof(*addr));
    
    printf("Executing server (PID: %d)\n", getpid());    
}
