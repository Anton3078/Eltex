#include "../../include/mysocket.h"

static int sockFd;
static int shmid;
int semid;
static struct data_transfer *dts;

void 
cleanup(int signo) 
{
    close(sockFd);
    shmdt(dts);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    exit(EXIT_SUCCESS);
}

int
main (int argc, char *argv[])
{   
    struct sockaddr_ll svaddr;
    struct packet pkt;

    if (argc != 4) errExit("Error: arguments");
    
    struct in_addr serv_ip_addr;
    if (inet_pton(AF_INET, argv[1], &serv_ip_addr) == -1)
       errExit("inet_pton");
    uint32_t serv_ip = serv_ip_addr.s_addr;
    unsigned int serv_port = atoi(argv[2]);
    char *interface = argv[3];
    
    //=Signal===============================================================
    struct sigaction sa;
    sa.sa_handler = cleanup;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGINT, &sa, NULL) == -1) errExit("sigaction");
    if (sigaction(SIGTERM, &sa, NULL) == -1) errExit("sigaction");
    //===============================================================Signal=
    
    //=Shared Memory===============================================================
    key_t keyShm;
    key_t keySem; 
        
    struct sembuf lock = {SEM_ACCESS, -1, 0};
    struct sembuf unlock = {SEM_ACCESS, 1, 0};
    struct sembuf notify = {SEM_NOTIFY, 1, 0};
    
    if ((keyShm = ftok(PATH_KEY_SHM, PROJ_SHM_ID)) == -1)
       errExit("ftok (shm)");
    
    if ((shmid = shmget(keyShm, sizeof(struct data_transfer), IPC_CREAT | 0660)) == -1)
       errExit("shmget");

    if ((dts = (struct data_transfer *) shmat(shmid, NULL, 0)) == (void *)-1)
       errExit("shmat");

    memset(dts, 0, sizeof(struct data_transfer));
    if ((keySem = ftok(PATH_KEY_SEM, PROJ_SEM_ID)) == -1)
       errExit("ftok (sem)");
    
    if ((semid = semget(keySem, 2, IPC_CREAT | 0660)) == -1)
       errExit("semget");

    semctl(semid, SEM_ACCESS, SETVAL, 1);
    semctl(semid, SEM_NOTIFY, SETVAL, 0);
    //=============================================================Shared Memory=
    
    //=Socket createting & setting=============================================
    if ((sockFd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
       errExit("socket");

    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sll_family = AF_PACKET;
    svaddr.sll_ifindex = if_nametoindex(interface);
    svaddr.sll_halen = ETH_ALEN;

    if (bind(sockFd, (struct sockaddr *)&svaddr, sizeof(svaddr)) == -1)
       errExit("bind");
    //============================================Socket createting & setting=
    for (int i = 0; i < MAX_SERVER; ++i) {
        if (fork() == 0) {
            handler_serv(dts);
        }
    }
    
    printf("====Server Start====\n");
    while (1) {
        struct sockaddr_ll cli_addr;
        socklen_t cli_addr_len = sizeof(cli_addr);
        if (recvfrom(sockFd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&cli_addr, &cli_addr_len) == -1) {
           perror("recvfrom");
           continue;
        }
        
        if (pkt.ip.protocol != IPPROTO_UDP || 
            pkt.ip.daddr != serv_ip ||
            pkt.udp.dest != htons(serv_port)) continue;
        pkt.payload.s_addr = cli_addr;
        
        pr_pkt_info(&pkt);
        
        if (memcmp(pkt.payload.mtext, "exit", 4) == 0) {
            semop(semid, &lock, 1);
            reset_client(dts, pkt.ip.saddr, ntohs(pkt.udp.source));
            semop(semid, &unlock, 1);
            continue;
        }

        semop(semid, &lock, 1);

        if (dts->pk_count < MAX_SERVER) {
            dts->pk_hist[dts->pk_count] = pkt;
            dts->pk_count++;
            semop(semid, &notify, 1);
        }

        semop(semid, &unlock, 1);
    }
}

