CC = gcc
CFLAGS = -Wall -Werror -I./include

SRC_LISTENER = src/listener.c
SRC_SENDER = src/sender.c 
OBJ_LISTENER = $(SRC_LISTENER:.c=.o)
OBJ_SENDER = $(SRC_SENDER:.c=.o)

TARGET_LISTENER = bin/listener
TARGET_SENDER = bin/sender

.PHONY: all clean dirs

all: dirs $(TARGET_LISTENER) $(TARGET_SENDER)

dirs:
	@mkdir -p bin

$(TARGET_LISTENER): $(OBJ_LISTENER)
	$(CC) -o $@  $(OBJ_LISTENER) 

$(TARGET_SENDER): $(OBJ_SENDER)
	$(CC) -o $@ $(OBJ_SENDER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_LISTENER) $(OBJ_SENDER)
	rm -f $(TARGET_LISTENER) $(TARGET_SENDER)
	rm -rf bin
