#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 5

void read_command(char *str);
void get_tokens(char **argVec, char *command);
#endif
