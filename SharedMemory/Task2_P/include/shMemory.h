#ifndef SHM_POSIX_H
#define SHM_POSIX_H

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_NAME "/p_shmemory"
#define SEM_NAME "/p_sem"
#define MAX_MSG_LEN 512

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
                     } while(0)

#endif
