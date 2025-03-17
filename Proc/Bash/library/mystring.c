#include <stdlib.h>
#include <stdio.h>

void
MyStr(char *str) {
    /*Записывает строку введёную строку в переменую str*/
    int ch;
    int index = 0;
    while((ch = getchar()) != EOF && ch != '\n') {
        str[index++] = (char ) ch;
    }
}
