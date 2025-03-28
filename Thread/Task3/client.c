#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int shops[5];
extern pthread_mutex_t mtx;

void *
client_func (void *shop)
{ /*take product from shop*/
    struct person * pers = (struct person *) shop;
    int index;
    int iter = 0;

    if (pers == NULL) {
        fprintf(stderr, "Error pounter !\n");
        pthread_exit(NULL);
    }

    while (pers->target != 0) {


        index = rand() % 5;
        pthread_mutex_trylock(&mtx);
        
        printf("==================================================================\n");
        printf("#%d Thread__client_%d has entred in %d shop\n", iter, pers->thread_id, index);

        if (index < 5 && index >= 0) {

            if (shops[index] > pers->target) {
                printf("#Thread_%d take %d product\n", pers->thread_id, pers->target);
                shops[index] -= pers->target;
                pers->target = 0;
            } else if (shops[index] <= pers->target) {
                printf("#Thread_%d take %d product\n", pers->thread_id, shops[index]);
                pers->target -= shops[index];
                shops[index] = 0;
            }
        } 
        printf("#Thread_%d current target - %d\n", pers->thread_id, pers->target);
        fflush(stdin);
        pthread_mutex_unlock(&mtx);
        iter++;
        sleep(2);
    }
    
    pthread_exit(NULL);
}   

