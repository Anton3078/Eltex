TARGET = mybash

CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = ./library/libBash.so.0 -Wl,-rpath,./library
SRCS = main.c
HEADERS = mystring.h pipe_utils.h command_utils.h
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET)

