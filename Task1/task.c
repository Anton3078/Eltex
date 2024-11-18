#include <stdio.h>

int main(void) {
    int num;
    
    printf("Введите целое положительное число: ");
    
    scanf("%d", &num);
    
    if (num < 0) {
        printf("Число отрицательное\n");
        return 1;
    }

    printf("Вы ввели: %b\n", num);

    return 0;
}
