CC = gcc
CFLAGS = -Wall -Werror -I./include -fPIC -g
LDFLAGS = -lncurses -pthread -lrt -L./lib -lchat
LIB_NAME = libchat.so.0.1
LIB_LINK = libchat.so

SRC_LIB = src/add_user.c src/remove_user.c src/broadcast.c #src/init_data.c
SRC_CLIENT = src/Client/client.c
SRC_SERVER = src/Server/server.c

OBJ_LIB = $(SRC_LIB:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

TARGET_LIB = lib/$(LIB_NAME)
TARGET_LINK = lib/$(LIB_LINK)
TARGET_CLIENT = bin/client
TARGET_SERVER = bin/server

.PHONY: all clean dirs

all: dirs $(TARGET_LIB) $(TARGET_LINK) $(TARGET_CLIENT) $(TARGET_SERVER)

dirs:
	@mkdir -p bin lib

$(TARGET_LIB): $(OBJ_LIB)
	$(CC) -shared -Wl,-soname,$(LIB_LINK) -o $@ $^
    

$(TARGET_LINK):
	ln -sf $(LIB_NAME) lib/$(LIB_LINK)

$(TARGET_CLIENT): $(OBJ_CLIENT) $(TARGET_LIB)
	$(CC) -o $@ $(OBJ_CLIENT) $(LDFLAGS) -Wl,-rpath,'$$ORIGIN/../lib'

$(TARGET_SERVER): $(OBJ_SERVER) $(TARGET_LIB)
	$(CC) -o $@ $(OBJ_SERVER) $(LDFLAGS) -Wl,-rpath,'$$ORIGIN/../lib'

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_LIB) $(OBJ_CLIENT) $(OBJ_SERVER)
	rm -f $(TARGET_LIB) $(TARGET_LINK) $(TARGET_CLIENT) $(TARGET_SERVER)
	rm -rf bin lib
