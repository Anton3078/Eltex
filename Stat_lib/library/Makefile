libcalc.a: add.o sub.o mul.o div.o
	ar rc libcalc.a add.o sub.o mul.o div.o

add.o: add.c calc.h
	gcc add.c calc.h -c -Wall -Werror


sub.o: sub.c calc.h
	gcc sub.c calc.h -c -Wall -Werror


mul.o: mul.c calc.h
	gcc mul.c calc.h -c -Wall -Werror

div.o: div.c calc.h
	gcc div.c calc.h -c -Wall -Werror
