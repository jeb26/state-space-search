OBJS = arraypass
CC = gcc

all: arraypass

arraypass:
	$(CC) arraypass.c -o arraypass

clean:
	rm -rf $(OBJS)
