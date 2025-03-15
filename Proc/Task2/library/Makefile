libproc.a: print_pid.o
	ar rc libproc.a *.o
	rm *.o

print_pid.o: print_pid.c
	gcc print_pid.c -c -Wall -Werror 

