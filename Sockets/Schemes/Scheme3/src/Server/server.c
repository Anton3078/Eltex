#include "../../include/mysocket.h"

int semid;

int
main ()
{   
    srand(time(NULL));

    int sockFd;
    struct sockaddr_in svaddr;
    struct ReqData *reqs;
    key_t keyShm;
    key_t keySem; 
    int shmid;
        
    struct sembuf lock = {SEM_ACCESS, -1, 0};
    struct sembuf unlock = {SEM_ACCESS, 1, 0};
    struct sembuf notify = {SEM_NOTIFY, 1, 0};
    
    if ((keyShm = ftok(PATH_KEY_SHM, PROJ_SHM_ID)) == -1)
       errExit("ftok (shm)");
    
    if ((shmid = shmget(keyShm, sizeof(struct ReqData), IPC_CREAT | 0660)) == -1)
       errExit("shmget");

    if ((reqs = (struct ReqData *) shmat(shmid, NULL, 0)) == (void *)-1)
       errExit("shmat");

    if ((keySem = ftok(PATH_KEY_SEM, PROJ_SEM_ID)) == -1)
       errExit("ftok (sem)");
    
    if ((semid = semget(keySem, 2, IPC_CREAT | 0660)) == -1)
       errExit("semget");

    semctl(semid, SEM_ACCESS, SETVAL, 1);
    semctl(semid, SEM_NOTIFY, SETVAL, 0);

    for (int i = 0; i < MAX_SERVER; ++i) {
        if (fork() == 0) {
            handler_serv(reqs);
        }
    }

    if ((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       errExit("socket");

    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(PORT);
    svaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockFd, (struct sockaddr *)&svaddr, sizeof(svaddr)) == -1)
       errExit("bind");

    while (1) {
        struct request req;
        socklen_t addr_len = sizeof(req.addr);

        if (recvfrom(sockFd, req.rtext, BUF_SIZE, 0, (struct sockaddr *)&req.addr, &addr_len) == -1)
           errExit("recvfrom");

        semop(semid, &lock, 1);
        
        if (reqs->ReqCount < MAX_SERVER + 5) {
            reqs->ReqHist[reqs->ReqCount] = req;
            reqs->ReqCount++;
            
            semop(semid, &notify, 1);
        } else {
            const char *busy_msg = "Server is busy";
            sendto(sockFd, busy_msg, strlen(busy_msg), 0, (struct sockaddr *)&req.addr, sizeof(req.addr));
        }

        semop(semid, &unlock, 1);
    }
}
