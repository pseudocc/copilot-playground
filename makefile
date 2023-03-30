# comiple list.c into list.o and liblist.so
# compile list.c into list_test with -DTEST
# use gcc as compiler

CC = gcc
CFLAGS = -Wall -g -fPIC
LDFLAGS = -shared

all: list.o liblist.so list_test

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

liblist.so: list.o
	$(CC) $(LDFLAGS) -o liblist.so list.o

list_test: list.c list.h
	$(CC) $(CFLAGS) -DTEST -o list_test list.c

clean:
	rm -f *.o *.so list_test
