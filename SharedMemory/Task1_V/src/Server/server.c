#include "../../include/shMemory.h"

int
main () 
{   
    
    key_t keyShm, keySem;
    int shmid, semid;
    char *shmaddr;


    struct sembuf lock[1] = {{0, -1, 0}};
//    struct sembuf unlock[2] = {{0, 1, 0}};
    
    char *str = "Hi!";

    if((keyShm = ftok(PATH_KEY_SHM, PROJ_SHM_ID)) == -1) {
        perror("ftok (shm)");
        exit(EXIT_FAILURE);  
    }

    
    if ((shmid = shmget(keyShm, MAX_MSG_LEN, IPC_CREAT | 0660)) == -1)
       errExit("shmget");

    if ((shmaddr = (char *) shmat(shmid, NULL, 0)) == (void *)-1)
       errExit("shmat");

    if ((keySem = ftok(PATH_KEY_SEM, PROJ_SEM_ID)) == -1)
       errExit("ftok (sem)");
    
    if ((semid = semget(keySem, 1, IPC_CREAT | 0660)) == -1)
       errExit("semget");
    
    memcpy(shmaddr, str, MAX_MSG_LEN);
    semop(semid, lock, 1);
    printf("%s\n", shmaddr);

    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, 0);
    semctl(semid, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}
