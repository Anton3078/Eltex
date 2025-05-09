#include "../../include/shMemory.h"

int 
main() 
{
    key_t keyShm, keySem;
    int shmid, semid;
    struct DataChat *chat;

    struct sembuf lock[1] = {{SEM_ACCESS, -1, 0}};
    struct sembuf unlock[1] = {{SEM_ACCESS, 1, 0}};
    struct sembuf wait_msg[1] = {{SEM_NOTIFY, -1, 0}};

    if ((keyShm = ftok(PATH_KEY_SHM, PROJ_SHM_ID)) == -1)
       errExit("ftok (shm)");
    
    if ((shmid = shmget(keyShm, sizeof(*chat), IPC_CREAT | 0660)) == -1)
       errExit("shmget");

    if ((chat = (struct DataChat *) shmat(shmid, NULL, 0)) == (void *)-1)
       errExit("shmat");

    if ((keySem = ftok(PATH_KEY_SEM, PROJ_SEM_ID)) == -1)
       errExit("ftok (sem)");
    
    if ((semid = semget(keySem, 2, IPC_CREAT | 0660)) == -1)
       errExit("semget");

    semctl(semid, SEM_ACCESS, SETVAL, 1);
    semctl(semid, SEM_NOTIFY, SETVAL, 0);

    printf("=== Server started ===\n");
    
    while (1) {
        semop(semid, wait_msg, 1);
        semop(semid, lock, 1);
        
        int msg_idx = (chat->msg_count - 1) % MAX_MSG;        
        struct Message *msg = &chat->msg_hist[msg_idx];
        switch (msg->type) {
            case USER_JOIN:
                printf("[+] %s joined. Users: %d\n", msg->sender, chat->usr_count);
                break;
            
            case CHAT_MSG:
                printf("[#] %s send message\n", msg->sender);
                break;
            
            case USER_LEAVE:
                printf("[-] %s left. Users: %d\n", msg->sender, chat->usr_count);
                break;
            
            default:
                fprintf(stderr, "Unknown message type\n");
        }
        semop(semid, unlock, 1);
    }

    shmdt(chat);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    exit(EXIT_FAILURE);
}
