#include <stdio.h> 

#define N 10

int main(void) {

    int vector[N];

    int i;

    for (i = 0; i < N; ++i) {
         scanf("%d", vector + i); 
         if(*(vector + i) < -2147483647 || *(vector + i)  > 2147483647) {
             printf("Выход за диапозон int\n");
             return 1;         
         }
    }

    for (i = 0; i < N; ++i) {
        if (i != N - 1)
            printf("%d ", *(vector + i));
        else
            printf("%d\n", *(vector + i));
    }

    return 0;
}
