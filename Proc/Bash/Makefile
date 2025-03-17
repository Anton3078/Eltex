main: main.o
	gcc main.o ./library/libmystring.so.0.1 -o main -Wl,-rpath,./library
	rm *.o *.h.*

main.o: main.c mystring.h
	gcc main.c mystring.h -c -Wall -Werror
