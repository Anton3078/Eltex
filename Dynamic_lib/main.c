#include <stdio.h>
#include "calc.h"


int main(void) {
    
    int num1, num2, result;
    char mode;


    printf("1) Сложение\n");
    printf("2) Вычитание\n");
    printf("3) Умножение\n");
    printf("4) Деление\n");
    printf("5) Выход\n");
    
    while(1) {

       scanf("%c", &mode);     

       switch(mode) {    
               case '1':
                     printf("Введите 1-ое число: ");
                     scanf("%d", &num1);
                     printf("Введите 2-ое число: ");
                     scanf("%d", &num2);
                     result = add(num1, num2);
                     printf("Result = %d\n", result);
                     break;

               case '2':
                     printf("Введите 1-ое число: ");
                     scanf("%d", &num1);
                     printf("Введите 2-ое число: ");
                     scanf("%d", &num2);
                     result = sub(num1, num2);
                     printf("Result = %d\n", result);
                     break;

               case '3':
                     printf("Введите 1-ое число: ");
                     scanf("%d", &num1);
                     printf("Введите 2-ое число: ");
                     scanf("%d", &num2);
                     result = mul(num1, num2);
                     printf("Result = %d\n", result);
                     break;

               case '4':
                     printf("Введите 1-ое число: ");
                     scanf("%d", &num1);
                     printf("Введите 2-ое число: ");
                     scanf("%d", &num2);

                     if (num2 == 0) {
                        perror("Zero division!");
                        return -1;
                     }

                     result = div(num1, num2);
                     printf("Result = %d\n", result);
                     break;

               case '5':
                     return 0;
                     break;
       }
    }
}
