#include <stdio.h>

#define N 5

int main(void) {

    int matrix[N][N];
    
    int i = 0;
    int j = 0;
    
    int num = 1;

    int index = 0; 

    while (num <= N * N) {
        matrix[i][j] = num;
        
        if (i == index && j < N - index - 1) {
            ++j;
        } else if (j == N - index - 1 && i < N - index - 1) {
            ++i;
        } else if (i == N - index - 1 && j > index) {
            --j;
        } else {
            --i;
        }

        if ((i == index + 1) && (j == index) && (index != N - index - 1)) {
              ++index;
        }

        ++num;  
    }



    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n\n");
    }

   return 0;
}
