main: main.o
	gcc -o main main.o -Llibrary -lproc
	rm *.o *.h.*

main.o: main.c print_pid.h
	gcc main.c print_pid.h -c -Wall -Werror
