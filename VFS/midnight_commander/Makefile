mc: mid_command_l.o
	gcc mid_command_l.o -o mc -L./library -lncurses -lMidComm -Wall -Werror
	rm *.o

mid_command_l.o: mid_command_l.c library/mid_command.h
	gcc mid_command_l.c library/mid_command.h -c -Wall -Werror
