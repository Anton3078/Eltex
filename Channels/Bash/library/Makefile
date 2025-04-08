TARGET = libBash.so.0.2
LINK = libBash.so.0

CC = gcc
CFLAGS = -Wall -Werror -fPIC -g
LDFLAGS = -Wl,-soname,libBash.so.0
SRCS = command_utils.c pipe_utils.c get_tokens.c mystring.c printf_info.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -shared $(OBJS) -o $(TARGET) $(LDFLAGS)
	ln -sf ./$(TARGET) $(LINK)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET) $(LINK)

.PHONY: all clean

