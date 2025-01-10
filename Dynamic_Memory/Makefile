main: main.o add.o remove.o getall.o findName.o equalStr.o clear.o
	gcc main.o add.o remove.o getall.o findName.o equalStr.o clear.o -o main
	

remove.o: remove.c struct.h
	gcc remove.c struct.h -c -Wextra -Wall -Werror -std=c89 -g
  
getall.o: getall.c struct.h
	gcc getall.c struct.h -c -Wextra -Wall -Werror -std=c89 -g


add.o: add.c struct.h
	gcc add.c struct.h -c -Wextra -Wall -Werror -std=c89 -g

findName.o: findName.c struct.h equalStr.h
	gcc findName.c equalStr.h struct.h -c -Wextra -Wall -Werror -std=c89 -g

equalStr.o: equalStr.c equalStr.h
	gcc equalStr.c equalStr.h -c -Wextra -Wall -Werror -std=c89 -g

clear.o: clear.c list.h struct.h
	gcc clear.c list.h struct.h -c -Wextra -Wall -std=c89 -g

main.o: main.c struct.h
	gcc main.c struct.h -c -Wextra -Wall -Werror -std=c89 -g
