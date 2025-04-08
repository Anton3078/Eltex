TARGET = serv

CC = gcc
CFLAGS = -Wall -Werror
SRCS = server.c
HEADERS = ../fifo_header.h
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g

clean: 
	rm -rf $(OBJS) $(TARGET)

.PHONY: all clean
