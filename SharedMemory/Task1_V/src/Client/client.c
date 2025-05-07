#include "../../include/shMemory.h"

int
main ()
{
    key_t keyShm, keySem;
    int shmid, semid;
    char *shmaddr;


//    struct sembuf lock[1] = {{0, -1, 0}};
    struct sembuf unlock[2] = {{0, 0, 0},
                               {0, 1, 0}};

    char *str = "Hello!";

    if ((keyShm = ftok(PATH_KEY_SHM, PROJ_SHM_ID)) == -1) {
        perror("ftok (shm)");
        exit(EXIT_FAILURE);  
    }
    
    if ((shmid = shmget(keyShm, MAX_MSG_LEN, 0)) == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if ((shmaddr = (char *) shmat(shmid, NULL, 0)) == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    if ((keySem = ftok(PATH_KEY_SEM, PROJ_SEM_ID)) == -1) {
        perror("ftok (sem)");
        exit(EXIT_FAILURE); 
    }
    
    if ((semid = semget(keySem, 1, 0)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", shmaddr);
    memcpy(shmaddr, str, MAX_MSG_LEN);
    semop(semid, unlock, 2);

    shmctl(shmid, IPC_RMID, 0);
    semctl(semid, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}


