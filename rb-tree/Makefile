CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -Wshadow -g #-DENABLE_VALGRIND

all: tests.x sample.x

test:
	make all
	./sample.x ./tests.x

tests.x: rb-tree.o tests.o
	$(CC) rb-tree.o tests.o memory-checking.o -o tests.x

sample.x: rb-tree.o sample.o
	$(CC) rb-tree.o sample.o -o sample.x

tests.o: rb-tree.h tests.c memory-checking.h
	$(CC) $(CFLAGS) -c tests.c

sample.o: rb-tree.h sample.c
	$(CC) $(CFLAGS) -c sample.c

rb-tree.o: rb-tree.h rb-tree.c
	$(CC) $(CFLAGS) -c rb-tree.c

rb-tree.h: rb-tree-datastructure.h
	touch rb-tree.h

clean:
	rm -f *~
	rm tests.x sample.x \
	tests.o rb-tree.o
