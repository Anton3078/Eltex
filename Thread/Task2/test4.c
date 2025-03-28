#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 4

long sum = 0;
pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;


void *
print_t (void* arg)
{ /*outputs thread num*/
    int i;
    int tmp = 0;
    
    for (i = 0; i < 45000000; ++i)
    {
        tmp++;
    }

    pthread_mutex_lock(&mt);
    sum += tmp;
    pthread_mutex_unlock(&mt);

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
    
    printf("sum = %ld\n", sum);

    exit(EXIT_SUCCESS);
}
