#include <stdio.h>

int
main (void)
{
    int i;
    int sum = 0;
    
    printf("Start calc!\n");
    
    for (i = 0; i < 180000000; ++i)
            sum++;
    
    printf("Sum = %d\n", sum);
}
