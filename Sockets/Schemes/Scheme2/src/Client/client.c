#include "../../include/mysocket.h"

int 
main() 
{
    int sock;
    struct sockaddr_in addr;
    char *msg = "Get current time";
    char resp[BUF_SIZE];
    ssize_t numBytes;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
       errExit("socket");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
       errExit("inet_pton");

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
       errExit("connect");

    send(sock, msg, strlen(msg), 0);
    printf("Message sent: %s\n", msg);

    if ((numBytes = recv(sock, resp, BUF_SIZE, 0)) == -1)
       errExit("recv");
    printf("Current time: %s\n", resp);

    if (close(sock) == -1)
       errExit("close");

    exit(EXIT_SUCCESS);
}
