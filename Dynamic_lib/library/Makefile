libcalc.so: add.o sub.o mul.o div.o
	gcc -shared add.o sub.o mul.o div.o -o libcalc.so

add.o: add.c
	gcc add.c -c -fPIC -Wall -Werror


sub.o: sub.c
	gcc sub.c -c -fPIC -Wall -Werror


mul.o: mul.c
	gcc mul.c -c -fPIC -Wall -Werror

div.o: div.c
	gcc div.c -c -fPIC -Wall -Werror
