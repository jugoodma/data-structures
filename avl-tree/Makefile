CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -Wshadow -g #-DENABLE_VALGRIND

all: tests.x sample.x

test:
	make all
	./tests.x

tests.x: avl-tree.o tests.o
	$(CC) avl-tree.o tests.o memory-checking.o -o tests.x

sample.x: avl-tree.o sample.o
	$(CC) avl-tree.o sample.o -o sample.x

tests.o: avl-tree.h tests.c memory-checking.h
	$(CC) $(CFLAGS) -c tests.c

sample.o: avl-tree.h sample.c
	$(CC) $(CFLAGS) -c sample.c

avl-tree.o: avl-tree.h avl-tree.c
	$(CC) $(CFLAGS) -c avl-tree.c

avl-tree.h: avl-tree-datastructure.h
	touch avl-tree.h

clean:
	rm -f *~
	rm tests.x sample.x \
	tests.o avl-tree.o
