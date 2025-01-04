#include <stdio.h>
#include "struct.h"
#include "list.h"
#include <malloc.h>
#include <stdlib.h>

int pop_front(struct list *guid) {
   
    if (guid == NULL) {
        printf("Error Pointer\nLine: %d\nfile: %s", __LINE__, __FILE__);
        return -1;
    }

    if (guid->size > 1) {        
        
        
        struct abonent* temp = guid->Head;    
            
        guid->Head = guid->Head->prevP;
        guid->Head->nextP = guid->Tail;
        guid->Tail->prevP = guid->Head;
        
        free(temp);

        --guid->size;

        return 0;

    } else if ( guid->size == 1) {
        
        struct abonent* temp = guid->Head;    
            
        free(temp);
        guid->Head = guid->Tail = NULL;

        --guid->size;

        return 0;
        
    } else {
        
        printf("Справочник пуст!\n");
        return 0;
    }
}

