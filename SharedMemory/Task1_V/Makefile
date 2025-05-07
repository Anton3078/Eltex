CC = gcc
CFLAGS = -Wall -Werror -g

SRC_CLIENT = src/Client/client.c
SRC_SERVER = src/Server/server.c
HEADERS = include/shMemeory.h

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

TARGET_CLIENT = bin/client
TARGET_SERVER = bin/server

.PHONY: all clean dirs

all: dirs $(TARGET_SERVER) $(TARGET_CLIENT)

dirs:
	@mkdir -p bin

$(TARGET_CLIENT): $(OBJ_CLIENT)
	$(CC) -o $@ $(OBJ_CLIENT)

$(TARGET_SERVER): $(OBJ_SERVER)
	$(CC) -o $@ $(OBJ_SERVER) 
	
clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	rm -f $(TARGET_CLIENT) $(TARGET_SERVER)
	rm -rf bin


