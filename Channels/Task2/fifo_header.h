#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVER_FIFO "/tmp/serv_fifo"
#define CLIENT_FIFO "/tmp/clent_fifo.%ld"
#define CLIENT_FIFO_LEN (sizeof(CLIENT_FIFO) + 20)

struct request {
    pid_t pid;
    int seqLen;
};

struct response {
    int seqNum;
};
