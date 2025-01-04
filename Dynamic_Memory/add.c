#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "struct.h"
#include "list.h"

int push_front(struct list *guid) {
    
    if (guid == NULL) { 
        printf("Error Pointer\nLine: %d\nfile: %s", __LINE__, __FILE__);
        return -1; 
    }

    struct abonent *new_peop = (struct abonent*) malloc(sizeof(struct abonent));

    if (new_peop == NULL) { 
        printf("Error Pointer\nLine: %d\nfile: %s", __LINE__, __FILE__);
        return -1; 
    }
        
    printf("Enter the name: ");
    scanf("%s", new_peop->name);

    printf("Enter the second name: ");
    scanf("%s", new_peop->second_name);
 
    printf("Enter the tel: ");
    scanf("%s", new_peop->tel);

    new_peop->prevP = new_peop->nextP = new_peop;
    
    if (guid->Head) {
       guid->Head->nextP = new_peop;
       guid->Tail->prevP = new_peop;     
       new_peop->prevP = guid->Head;
       new_peop->nextP = guid->Tail; 
       guid->Head = new_peop;    
       ++guid->size;
            
    } else {
        guid->Head = guid->Tail = new_peop;
        guid->size = 1;
    }
    
    printf("Абоненет успешно добавлен!\n");
    return 0;    
}

