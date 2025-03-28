#include "person.h"
#include <stdlib.h>
#include <stdio.h>

struct person *
clients_init (int person_num)
{
    int i;
    struct person *clients;

    clients = (struct person *) calloc(person_num, sizeof(*clients));
    
    if (clients == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < person_num; ++i) {
        clients[i].thread_id = i + 1;
        clients[i].target = 10000 + (rand() % (2000 + 1));
    }

    return clients;
}
