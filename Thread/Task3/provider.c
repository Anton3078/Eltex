#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern pthread_mutex_t mtx;
extern int shops[5];

void *
provider_func (void *shop)
{/*uploads 500 product to shop*/
    struct person *pers = (struct person *) shop;
    int index;
    int iter;    

    if (pers == NULL) {
        perror("Error pointer!\n");
        pthread_exit(NULL);
    }

    while (1) {
        
        index = rand() % 5;
        
        pthread_mutex_trylock(&mtx);

        printf("==========================================================\n");
        printf("#%d Thre_provider_%d has entered in %d shop\n", iter, pers->thread_id, index);

        if (index < 5 && index >= 0) {
           shops[index] += 500;
           printf("#Thread_provider_%d loaded 500 product\n", pers->thread_id);
           
        }
        fflush(stdin);
        pthread_mutex_unlock(&mtx);
        iter++;
        sleep(1);
    }

    pthread_exit(NULL);
}
