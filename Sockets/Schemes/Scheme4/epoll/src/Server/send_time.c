#include "../include/mysocket.h"

void
send_time (struct con_addr * connection)
{
    time_t tim;
    struct tm *timeinfo;
    char buf[80];
    
    time(&tim);
    timeinfo = localtime(&tim);
    
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    if (connection->proto == TCP) {
        send(connection->sockFd, buf, strlen(buf), 0);
    } else if (connection->proto == UDP) {
        sendto(connection->sockFd, buf, strlen(buf), 0, connection->addr, connection->addr_size);
    }

    printf("Executing server for %s client\n", connection->proto == TCP ? "TCP" : "UDP");    
}
