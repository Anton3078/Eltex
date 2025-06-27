#include "../include/cli_utils.h"

void 
read_command(char *str) 
{
    int ch;
    int index = 0;
    while((ch = getchar()) != EOF && ch != '\n' && index < 127) {
        str[index++] = (char)ch;
    }
    str[index] = '\0';
}

void 
get_tokens(char** argVec, char* command) 
{ /*Делит строку command на токены
    и сохраняет их в argVec*/
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

