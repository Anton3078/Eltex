CC = gcc
CFLAGS = -Wall -Werror -I./include -g -fPIC
LDFLAGS = -Wl,-rpath='$$ORIGIN/../lib'
LIB_LDFLAGS = -shared -Wl,-soname,libmysocket.so.0

SRC_CLIENT = src/Client/client.c
SRC_SERVER = src/Server/serv_ls.c src/Server/exec_serv.c
SRC_LIB = src/socket_utils.c
HEADERS = include/mysocket.h

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_LIB = $(SRC_LIB:.c=.o)

TARGET_CLIENT = bin/client
TARGET_SERVER = bin/server
LIB_TARGET = lib/libmysocket.so.0.1
LIB_LINK = lib/libmysocket.so.0

.PHONY: all clean dirs

all: dirs $(LIB_TARGET) $(TARGET_SERVER) $(TARGET_CLIENT)

dirs:
	@mkdir -p bin lib

$(LIB_TARGET): $(OBJ_LIB)
	$(CC) $(LIB_LDFLAGS) -o $@ $^
	ln -sf $(notdir $(LIB_TARGET)) $(LIB_LINK)
	ln -sf $(notdir $(LIB_LINK)) lib/libmysocket.so

$(TARGET_CLIENT): $(OBJ_CLIENT) $(LIB_TARGET)
	$(CC) $(LDFLAGS) -o $@ $< -L./lib -lmysocket

$(TARGET_SERVER): $(OBJ_SERVER) $(LIB_TARGET)
	$(CC) $(LDFLAGS) -o $@ $(filter-out $(LIB_TARGET),$^) -L./lib -lmysocket

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_LIB)
	rm -f $(TARGET_CLIENT) $(TARGET_SERVER) $(LIB_TARGET) $(LIB_LINK) lib/libmysocket.so
	rm -rf bin lib
