#include <stdlib.h>
#include <stdio.h>

#define MAX_COMMAND_LEN 1024

void
MyStr(char *str) {
    /*Записывает строку введёную строку в переменую str*/
    int ch;
    int index = 0;

    while((ch = getchar()) != EOF && ch != '\n' && index < MAX_COMMAND_LEN) {
        str[index++] = (char ) ch;
    }

    str[index] = '\0';

    while (index > 0 && (str[index - 1] == ' ' || str[index - 1] == '\t')) str[--index] = '\0';
}
