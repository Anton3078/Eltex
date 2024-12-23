main: task.o
	gcc task.o -o main

task.o: task.c struct.h
	gcc task.c struct.h -c -Wextra -Wall -Werror -std=c89  task.o 
