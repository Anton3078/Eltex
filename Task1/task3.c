#include <stdio.h>

int main(void) {
    int num;
    int count = 0;
    
    printf("Введите целое положительное число: ");
    
    scanf("%d", &num);
    
    if (num < 0) {
        printf("Число отрицательное\n");
        return 0;
    }
   
    
    for (int i = 0; i < sizeof(num) - 1; ++i) {
        if (0b1 == ((num >> i) & 0b1)) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
