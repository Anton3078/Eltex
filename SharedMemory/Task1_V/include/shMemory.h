#ifndef _SHMEMORY_H
#define _SHMEMORY_H

#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>

#define PATH_KEY_SHM "/dev/shm/my_shm_key"
#define PATH_KEY_SEM "/dev/shm/my_sem_key"
#define PROJ_SHM_ID 'S'
#define PROJ_SEM_ID 'A'
#define MAX_MSG_LEN 8
#define MAX_MSG 4
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
                     } while(0)


#endif
