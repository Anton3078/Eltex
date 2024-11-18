#include <stdio.h>

#define N 5

int main(void) {

    int vector[N];
    int revers_vector[N];

    int i;

    for (i = 0; i < N; ++i) {
        scanf("%d", &vector[i]); 
        if(vector[i] < -2147483647 || vector[i]  > 2147483647) {
            printf("Выход за диапозон int\n");
            return 1;
        }
    }

    for (i = 0; i < N; ++i) {
        printf("%d ", vector[i]);
    }
    
    printf("\n");

    for (i = 0; i < N; ++i) {
        revers_vector[i] = vector[N - i - 1];
    }

    for (i = 0; i < N; ++i) {
        printf("%d ", revers_vector[i]);
    }
    

    return 0;
}
