#include <stdio.h>

int main(void) {
    int num;
    
    printf("Введите целое положительное число: ");
    
    scanf("%d", &num);
    
    if (num >= 0) {
        printf("Число положительно или равно 0\n");
        return 0;
    }

    printf("Вы ввели: %b\n", num, num);

    return 0;
}
