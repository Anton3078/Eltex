#include <stdio.h>

#define N 6

int main(void) {

    int matrix[N][N];
    
    int i, j;
    
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            if (j >= (N - 1) - i) {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
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
