#include <stdio.h>

#define N 3


int main(void) {

    int matrix[N][N];
    int num = 1;

    int i, j;

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            matrix[i][j] = num;
            ++num;  
        }
    }

   for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
             if(N - 1 != j) {
                printf("%d ", matrix[i][j]);
             } else {
                printf("%d", matrix[i][j]);
 
             }  
        }
        printf("\n");
    }

    return 0;
}
