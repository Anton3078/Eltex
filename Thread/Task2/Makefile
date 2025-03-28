all: test1 test2 test3 test4 test5

test1: test1.c
	gcc test1.c -o test1 -Wall -Werror

test2: test2.c
	gcc test2.c -o test2 -lpthread -Wall -Werror

test3: test3.c
	gcc test3.c -o test3 -lpthread -Wall -Werror

test4: test4.c
	gcc test4.c -o test4 -lpthread -Wall -Werror

test5: test5.c
	gcc test5.c -o test5 -lpthread -Wall -Werror

clean:
	rm -rf *.o test1 test2 test3 test4 test5
