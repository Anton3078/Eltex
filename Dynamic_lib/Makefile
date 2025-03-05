main: main.o
	gcc main.o -o main -L./library/ -lcalc

main.o: main.c calc.h
	gcc main.c calc.h -c -Wall -Werror
