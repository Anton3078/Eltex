#include "list.h"
#include <stdio.h>
int clear (struct list* guid) {

     if (guid == NULL) {
         printf("Error Pointer: line -> %d file -> %s\n", __LINE__, __FILE__);
         return -1;
     }

    while(guid->size) {
        if (pop_front(guid) == -1) {
            return -1;
        }
    }

    return 0;
}
