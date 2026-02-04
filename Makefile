CC = gcc
CFLAGS = -Wall -g

# List your files here
SRCS = src/main.c src/allocator.c src/list_ops.c src/utils.c
TARGET = allocator_demo

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
