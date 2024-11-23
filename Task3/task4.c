#include <stdio.h>

#define N 50

int main(void) {

    
    char str[N];
    char substr[N];

    char* strP = str;
    char* substrP = substr;
    char* P3;
    char* start_substr = NULL;
   
    printf("Введите строку: ");
    scanf("%s", str);

    printf("Введите подстроку: ");
    scanf("%s", substr);

    while (*strP) {
        if (*strP == *substrP) {       

            P3 = strP;
            start_substr = strP;

            while (*substrP) {
                if ( *P3 == *substrP) {
                    ++P3;
                    ++substrP;
                } else {
                    start_substr = NULL;
                    break;
                }
            }

            substrP = substr;
     
            if (start_substr) {
                break;
            }
     
        }
        ++strP;
    }
    
    printf("%p\n", start_substr);

    return 0;
    
}
