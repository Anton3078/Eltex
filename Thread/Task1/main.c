#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 5

void *
print_t (void* arg)
{ /*outputs thread num*/
    int *num = (int *)arg;
    printf("thread num = %d\n", *num);
    
    return NULL;
}

int
main (void) 
{
    pthread_t threads[N];
    int *stat;
    int Vec[N];
    int i, j;

    for (i = 0; i < N; ++i)
    {
        Vec[i] = i;
        pthread_create(&threads[i], NULL, print_t, (void *)&Vec[i]);
    }

    for (j = 0; j < N; ++j)
    {
        pthread_join(threads[j], (void **) &stat);
    }

    exit(EXIT_SUCCESS);
}
