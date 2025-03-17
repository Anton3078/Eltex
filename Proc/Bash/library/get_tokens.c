#include <string.h>
#include <stdlib.h>

void 
get_tokens(char** argVec, char* command) {
    /*Делит строку command на токены и сохраняет их в argVec*/
    char *str, *token;
    char *saveptr;
    int i;


    for (i = 0, str = command; ; ++i, str = NULL) {
       token = strtok_r(str, " ", &saveptr);
       
       if (token == NULL)
          break;
       argVec[i] = token;
    }
}
