#include <stdio.h>
#include "struct.h"
#include "list.h"

int GetAll(struct list* guid) {

    if (guid == NULL) {
        printf("Error Pointer\nLine: %d\nfile: %s", __LINE__, __FILE__);
        return -1;
    }

    struct abonent* cur_peop = guid->Tail;
    int i;
    
    for (i = 0; i < guid->size; ++i) {

        printf("=================================================\n");
        printf("Name: %s\n", cur_peop->name);
        printf("-------------------------------------------------\n");
        printf("Second name: %s\n", cur_peop->second_name);
        printf("-------------------------------------------------\n");
        printf("Phone: %s\n", cur_peop->tel);
        printf("=================================================\n");
        
        cur_peop = cur_peop->nextP;

    }

    return 0;
}

