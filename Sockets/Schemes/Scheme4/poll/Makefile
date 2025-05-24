CC = gcc
CFLAGS = -Wall -Werror -I./include -g
LDFLAGS = -pthread

SRC_CLIENT_TCP = src/Client/client.c
SRC_CLIENT_UDP = src/Client/client_udp.c
SRC_SERVER = src/Server/server.c src/Server/send_time.c
HEADERS = include/mysocket.h

OBJ_CLIENT_TCP = $(SRC_CLIENT_TCP:.c=.o)
OBJ_CLIENT_UDP = $(SRC_CLIENT_UDP:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

TARGET_CLIENT_TCP = bin/client_tcp
TARGET_CLIENT_UDP = bin/client_udp
TARGET_SERVER = bin/server

.PHONY: all clean dirs

all: dirs $(TARGET_SERVER) $(TARGET_CLIENT_TCP) $(TARGET_CLIENT_UDP)

dirs:
	@mkdir -p bin

$(TARGET_CLIENT_TCP): $(OBJ_CLIENT_TCP)
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET_CLIENT_UDP): $(OBJ_CLIENT_UDP)
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET_SERVER): $(OBJ_SERVER)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT_TCP) $(OBJ_SERVER) $(OBJ_CLIENT_UDP)
	rm -f $(TARGET_CLIENT_TCP) $(TARGET_SERVER) $(TARGET_CLIENT_UDP)
	rm -rf bin
