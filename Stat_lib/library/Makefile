libcalc.a: add.o sub.o mul.o div.o
	ar rc libcalc.a add.o sub.o mul.o div.o

add.o: add.c
	gcc add.c -c -Wall -Werror


sub.o: sub.c
	gcc sub.c -c -Wall -Werror


mul.o: mul.c
	gcc mul.c -c -Wall -Werror

div.o: div.c
	gcc div.c -c -Wall -Werror
