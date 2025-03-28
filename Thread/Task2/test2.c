#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 4

long a = 0;

void *
print_t (void* arg)
{ /*outputs thread num*/
    int i;

    for (i = 0; i < 45000000; ++i)
            a++;
    
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
    
    printf("sum = %ld\n", a);

    exit(EXIT_SUCCESS);
}
