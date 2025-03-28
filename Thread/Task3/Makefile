TARGET = main

CC = gcc
CFLAGS = -Wall -Werror -Wextra -lpthread
SRCS = main.c clients_init.c client.c provider.c
HEADERS = person.h
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET)

.PHONY: all clean
