CC = gcc
CFLAGS = -Wall -Werror -I./include -g
LDFLAGS = -pthread -g

SRC_CLIENT = src/Client/client.c
SRC_SERVER = src/Server/server.c src/send_time.c src/Server/exec_serv.c
HEADERS = include/mysocket.h

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

TARGET_CLIENT = bin/client
TARGET_SERVER = bin/server

.PHONY: all clean dirs

all: dirs $(TARGET_SERVER) $(TARGET_CLIENT)

dirs:
	@mkdir -p bin

$(TARGET_CLIENT): $(OBJ_CLIENT)
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET_SERVER): $(OBJ_SERVER)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	rm -f $(TARGET_CLIENT) $(TARGET_SERVER)
	rm -rf bin
