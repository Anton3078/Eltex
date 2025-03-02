libcalc.a: add.o sub.o mul.o div.o
	gcc -shared add.o sub.o mul.o div.o -o libcalc.so

add.o: add.c calc.h
	gcc add.c calc.h -c -fPIC -Wall -Werror


sub.o: sub.c calc.h
	gcc sub.c calc.h -c -fPIC -Wall -Werror


mul.o: mul.c calc.h
	gcc mul.c calc.h -c -fPIC -Wall -Werror

div.o: div.c calc.h
	gcc div.c calc.h -c -fPIC -Wall -Werror
