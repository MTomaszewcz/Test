CFLAGS=-g -Wall -ggdb -std=c99
CC=gcc

zad1.o: zad1.c
	$(CC) $(CFLAGS) -c -o $@ $^

zad1: zad1.o
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -f *.o core.#
	@echo "czysto"

zip: *.c makefile
	zip arch.zip $^

