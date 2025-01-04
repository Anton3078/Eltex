#include <stdio.h>
#include "struct.h"
#include "equalStr.h"
#include "list.h"

int Find(struct list* guid) {

     int i;
     char name_f[10] = "";
     struct abonent* cur_peop = guid->Tail;

     printf("Введите имя абонента: ");
     scanf("%s", name_f);

     for (i = 0; i < guid->size; i++) {
         if(equals_str(name_f, cur_peop->name)) {
            
            printf("=================================================\n");
            printf("Name: %s\n", cur_peop->name);
            printf("-------------------------------------------------\n");
            printf("Second name: %s\n", cur_peop->second_name);
            printf("-------------------------------------------------\n");
            printf("Phone: %s\n", cur_peop->tel);
            printf("=================================================\n");
            
            return 0; 
         }

         cur_peop = cur_peop->nextP;
     }
     
     printf("Абонент не найден\n");
     return 0;
 }
