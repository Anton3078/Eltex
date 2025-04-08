#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 32

void 
get_tokens(char** argVec, char *command, char *sep) {

    /*Делит строку command на токены и сохраняет их в argVec*/
    char *token;
    char *saveptr = NULL;
    int i = 0;
    
    memset(argVec, 0, MAX_ARGS * sizeof(char *));

    token = strtok_r(command, sep, &saveptr);
    while (token != NULL && i < MAX_ARGS - 1) {
        if (*token != '\0') {
          argVec[i++] = token;
        }
        
        token = strtok_r(NULL, sep, &saveptr);
    }

    argVec[i] = NULL;
}
