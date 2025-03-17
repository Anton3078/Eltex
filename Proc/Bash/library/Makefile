libmystring.so.0.1: get_tokens.o mystring.o
	gcc -shared *.o -o libmystring.so.0.1 -Wl,-soname,libmystring.so.0
	rm *.o

get_tokens.o: get_tokens.c
	gcc -c -fPIC get_tokens.c -Wall -Werror

mystring.o: mystring.c
	gcc -c -fPIC mystring.c -Wall -Werror

