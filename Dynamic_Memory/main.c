#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "struct.h"
#include "list.h"


int main(void) {

    char mode;
    /*short capacity = 0;*/
    
    /*
    struct abonent guide[N] = {0};
    struct abonent *HEAD = guide;
    */

    struct list guid;

    printf("1) Добавить абонента\n");
    printf("2) Удалить абонента\n");
    printf("3) Поиск абонента по имени\n");
    printf("4) Вывод всез записей\n");
    printf("5) Выход\n");
  
        
    while(1) {
        
       scanf("%c", &mode);     

       switch(mode) {    
               case '1':
                     push_front(&guid);
                     break;

               case '2':
                     pop_front(&guid);
                     break;

               case '3':
                     Find(&guid);
                     break;

               case '4':
                     GetAll(&guid);
                     break;

               case '5':
                     clear(&guid);
                     return 0;
                     break;
       }
    }
}
