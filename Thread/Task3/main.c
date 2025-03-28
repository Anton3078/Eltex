#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include <signal.h>

#define CLIENT_N 3

int shops[5]; 
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int
main (void) 
{
    struct person *clients;
    struct person provider;

    int *stat1;
    int *stat2;

    size_t i, k, j; 
    for (i = 0; i < sizeof(shops)/sizeof(shops[0]); ++i) 
    {
        shops[i] = 500;
    }

    clients = clients_init(CLIENT_N);
    provider.thread_id = 0;
    provider.target = 500;
    
    for (j = 0; j < CLIENT_N; ++j)
    {
        pthread_create(&clients[j].thread, NULL, client_func, (void *) &clients[j]);
    }
    
    pthread_create(&provider.thread, NULL, provider_func, (void *) &provider);

    for (k = 0; k < CLIENT_N; ++k)
    {
        pthread_join(clients[k].thread, (void **) &stat1);
    }
    
    pthread_kill(provider.thread, SIGTERM);
    pthread_join(provider.thread, (void **) &stat2);
    
    free(clients); 
    exit(EXIT_SUCCESS);
}
