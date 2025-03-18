libMidComm.a: open_dir.o read_dir.o draw_panel.o fexecut.o
	ar rc libMidComm.a *.o
	rm *.o *.h.*

open_dir.o: open_dir.c
	gcc open_dir.c -c -Wall -Werror

read_dir.o: read_dir.c
	gcc read_dir.c -c -Wall -Werror

draw_panel.o: draw_panel.c
	gcc draw_panel.c -c -Wall -Werror

fexecut.o: fexecut.c
	gcc fexecut.c -c -Wall -Werror
