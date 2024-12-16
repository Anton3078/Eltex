#include <stdio.h>
#include "struct.h"

int equals_str(char *, char *);

int main(void) {

    char mode;
    short capacity = 0;

    struct abonent guide[N] = {0};
    struct abonent *HEAD = guide;

    printf("1) Добавить абонента\n");
    printf("2) Удалить абонента\n");
    printf("3) Поиск абонента по имени\n");
    printf("4) Вывод всез записей\n");
    printf("5) Выход\n");
        
    while(1) {
    
       scanf("%c", &mode);     

       switch(mode) {    
               case '1':
                     Add(&HEAD, &capacity);
                     break;

               case '2':
                     Remove(&HEAD, &capacity);
                     break;

               case '3':
                     Find(guide);
                     break;

               case '4':
                     GetAll(guide);
                     break;

               case '5':
                     return 0;
                     break;
       }
    }
}

void Add(struct abonent **Head, short *capacity) {
     
    if (*capacity != N) {

        printf("Enter the name: ");
        scanf("%s", (* Head)->name);

        printf("Enter the second name: ");
        scanf("%s", (* Head)->second_name);

        printf("Enter the tel: ");
        scanf("%s", (* Head)->tel);
        
        printf("Абоненет успешно добавлен!\n");

        ++*Head;
        ++*capacity;
    } else {
        printf("Переполнение справочника\n");
    }
}

void Remove(struct abonent **Head, short *capacity) {
    if (*capacity != 0) {
        --*Head;
        printf("Name: %s\nSurname: %s\nPhone: %s\n", (*Head)->name, (*Head)->second_name, (*Head)->tel);
        *(*Head)->name = 0;
        *(*Head)->second_name = 0;
        *(*Head)->tel = 0;
        --*capacity;
    } else {
        printf("Справочник пуст\n");
    }
}

void GetAll(struct abonent abon[N]) {
    int i;
    for (i = 0; i < N; ++i) {
        printf("%d===================================================================================\n", i);
        printf("Name: %s\nSecond name: %s\nPhone: %s\n", abon[i].name, abon[i].second_name, abon[i].tel);
        printf("====================================================================================\n"); 
    }
}

void Find(struct abonent abon[N]) {
    
    int i;
    char name_f[10] = "";

    printf("Введите имя абонента: ");
    scanf("%s", name_f);

    for (i = 0; i < N; i++) {
        if(equals_str(name_f, abon[i].name)) {
            printf("Name: %s\nSecond name: %s\nPhone: %s\n", abon[i].name,abon[i].second_name, abon[i].tel);
            printf("===========================================\n");
        }
    }
}

int equals_str(char *fin_name, char *name) {
   
   int flag = 1;
            
   while(*fin_name) {
   
       if (*fin_name == *name) {
           ++fin_name;
           ++name;
       } else {
           flag = 0;
           break;
       }
   }

   if (flag) {
       return 1;
   } else {
       return 0;
   }
}

