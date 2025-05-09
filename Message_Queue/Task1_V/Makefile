CC = gcc
CFLAGS = -Wall -Werror -I./include -fPIC
LDFLAGS = -L./lib -lmsgqueue

SRC_LIB = src/get_msg.c src/send_msg.c
SRC_CLIENT = src/Client/client.c
SRC_SERVER = src/Server/server.c

OBJ_LIB = $(SRC_LIB:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

LIB_NAME = libmsgqueue.so
TARGET_LIB = lib/$(LIB_NAME)
TARGET_LIB_LINK = lib/$(LIB_NAME).0
TARGET_CLIENT = bin/client
TARGET_SERVER = bin/server
TARGET_QUEUE = /tmp/my_msg_queue

.PHONY: all clean

all: $(TARGET_LIB) $(TARGET_LIB_LINK) $(TARGET_CLIENT) $(TARGET_SERVER) $(TARGET_QUEUE)

$(TARGET_LIB): $(OBJ_LIB)
	@mkdir -p lib
	$(CC) -shared -o $@ $^

$(TARGET_LIB_LINK): $(TARGET_LIB)
	ln -sf $(LIB_NAME) $@

$(TARGET_CLIENT): $(OBJ_CLIENT) $(TARGET_LIB)
	@mkdir -p bin
	$(CC) -o $@ $(OBJ_CLIENT) $(LDFLAGS) -Wl,-rpath,'$$ORIGIN/../lib'

$(TARGET_SERVER): $(OBJ_SERVER) $(TARGET_LIB)
	$(CC) -o $@ $(OBJ_SERVER) $(LDFLAGS) -Wl,-rpath,'$$ORIGIN/../lib'

$(TARGET_QUEUE):
	@touch /tmp/my_msg_queue

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_LIB) $(OBJ_CLIENT) $(OBJ_SERVER)
	rm -f $(TARGET_LIB) $(TARGET_LIB_LINK) $(TARGET_CLIENT) $(TARGET_SERVER)
	rm -f $(TARGET_QUEUE)
	rm -rf bin lib

