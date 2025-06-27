CC = gcc
CFLAGS = -Wall -Werror -g -I./include
LDFLAGS = -lrt -lpthread

SRC_CLI_UTILS = src/cli_utils.c
SRC_DRIVER = src/drive_utils.c src/handle_driver.c
SRC = src/main.c

OBJ_CLI_UTILS = $(SRC_CLI_UTILS:.c=.o)
OBJ_DRIVER = $(SRC_DRIVER:.c=.o)
OBJ = $(SRC:.c=.o)

TARGET = bin/taxi_manager
LIB_CLI_UTILS = lib/libcli_utils.so
LIB_DRIVER = lib/libdriver_core.so

.PHONY: all clean dirs

all: dirs $(LIB_CLI_UTILS) $(LIB_DRIVER) $(TARGET)

dirs:
	@mkdir -p bin lib

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) -L./lib -lcli_utils -ldriver_core $(LDFLAGS) -Wl,-rpath='$$ORIGIN/../lib'

$(LIB_CLI_UTILS): $(OBJ_CLI_UTILS)
	$(CC) -shared -o $@ $(OBJ_CLI_UTILS)
	ln -sf $(shell pwd)/$@ $(shell pwd)/lib/libcli_utils.so.1

$(LIB_DRIVER): $(OBJ_DRIVER)
	$(CC) -shared -o $@ $(OBJ_DRIVER) $(LDFLAGS)
	ln -sf $(shell pwd)/$@ $(shell pwd)/lib/libdriver_core.so.1

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLI_UTILS) $(OBJ_DRIVER) $(OBJ)
	rm -f $(TARGET) $(LIB_CLI_UTILS) $(LIB_DRIVER) lib/libcli_utils.so.1 lib/libdriver_core.so.1
	rm -rf bin lib
