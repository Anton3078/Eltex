CC = gcc
CFLAGS = -Wall -Werror -g

SRC_CLIENT = src/client.c
SRC_SERVER = src/server.c
HEADERS = include/shMemeory.h

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

TARGET_CLIENT = bin/client
TARGET_SERVER = bin/server
TARGET_SOCK = /tmp/my_sock_path

.PHONY: all clean dirs

all: dirs $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_SOCK)

dirs:
	@mkdir -p bin

$(TARGET_CLIENT): $(OBJ_CLIENT)
	$(CC) -o $@ $(OBJ_CLIENT)

$(TARGET_SERVER): $(OBJ_SERVER)
	$(CC) -o $@ $(OBJ_SERVER) 

$(TARGET_SOCK):
	@touch $(TARGET_SOCK)

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	rm -f $(TARGET_CLIENT) $(TARGET_SERVER) $(TARGET_SOCK)
	rm -rf bin

