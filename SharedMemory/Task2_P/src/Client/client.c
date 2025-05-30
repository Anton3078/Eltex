#include "../../include/shMemory.h"

int
main ()
{
    int shm_fd;
    char *msg;
    char *str = "Hello!";

    sem_t * sem;

    if ((sem = sem_open(SEM_NAME, O_RDWR)) == SEM_FAILED)
       errExit("sem_open");

    if ((shm_fd = shm_open(SHM_NAME, O_RDWR, 0660)) == -1)
       errExit("shm_open");
    
    msg = (char *) mmap(NULL, MAX_MSG_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("%s\n", msg);
    memcpy(msg, str, strlen(str));
    sem_post(sem);

    munmap(msg, MAX_MSG_LEN);
    sem_close(sem);
    sem_unlink(SEM_NAME);
    shm_unlink(SHM_NAME);

    exit(EXIT_SUCCESS);

}
