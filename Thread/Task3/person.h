#ifndef _PERSON_H_
#define _PERSON_H_

#include <pthread.h>

struct person 
{
    pthread_t thread;
    int thread_id;
    int target;
    int is_provid;
};
struct person *clients_init(int);
void *client_func(void *);
void *provider_func(void *);

#endif
