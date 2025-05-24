#include "../../include/mysocket.h"

int 
main() 
{
    int sock;
    struct sockaddr_in addr;
    char msg[BUF_SIZE] = "Get current time";
    char resp[BUF_SIZE];

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
       errExit("inet_pton");

    if (sendto(sock, msg, strlen(msg), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1)
       errExit("sendto");

    socklen_t addr_len = sizeof(addr);
    if (recvfrom(sock, resp, BUF_SIZE, 0, (struct sockaddr *)&addr, &addr_len) == -1)
       errExit("recvfrom");
    printf("Current time: %s\n", resp);

    if (close(sock) == -1)
       errExit("close");
    
    exit(EXIT_SUCCESS);
}
