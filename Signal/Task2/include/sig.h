#ifndef SIG_H
#define SIG_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)

#endif 
