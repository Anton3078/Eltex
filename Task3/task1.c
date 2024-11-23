#include <stdio.h>


int main(void) {
    long int num;
    int usr_num;
    const long int MAX_INT = 4294967295;
    const int MAX_Byte = 255;
    char* nump;
 
    printf("Введите первое целое положительное число: ");
     
    scanf("%ld", &num); 
    
    if (num < 0) {
        printf("Число отрицательное\n");
        return 0;
    } else if (num > MAX_INT) {
       printf("Выход за диапозон\n"); 
       return 0;
    }

    nump = &num;

    
    printf("Введите второе целое положительное число: ");
    
    scanf("%d", &usr_num);
    
    if (usr_num < 0) {
        printf("Число отрицательное\n");
        return 0;
    } else if (usr_num > MAX_Byte) {
       printf("Выход за диапозон одного байта\n"); 
       return 0;
    }    
    
    *(nump + 2) = usr_num;

    printf("Новое значение = %ld %lb\n", num, num);
    


    return 0;
    
}
