#include "../../include/shMemory.h"

int
main () 
{
    int shm_fd;
    char *msg;
    char *str = "Hi!";

    sem_t *sem;
    
    if ((sem = sem_open(SEM_NAME, O_CREAT | O_RDWR, 0660, 0)) == SEM_FAILED)
       errExit("sem_open");

    if ((shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0660)) == -1)
       errExit("shm_open");

    ftruncate(shm_fd, MAX_MSG_LEN);
    
    msg = (char *) mmap(NULL, MAX_MSG_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    memcpy(msg, str, strlen(str));
    sem_wait(sem);
    printf("%s\n", msg);

    munmap(msg, MAX_MSG_LEN);
    sem_close(sem);
    sem_unlink(SEM_NAME);
    shm_unlink(SHM_NAME);

    exit(EXIT_SUCCESS);
}
