#ifndef PIPE_UTILS_H
#define PIPE_UTILS_H

#include <unistd.h>

void create_pipe(int [2]);
void redirect_output(int [2]);
void redirect_input(int [2]);
void close_pipe(int [2]);

#endif
