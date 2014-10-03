CC=gcc
CFLAGS=-g -I

all: first

first: lex.yy.c llist.o plist.o rdparser.o
	$(CC) -g lex.yy.c llist.o plist.o rdparser.o -ll -o bin/first

lex.yy.c: first.l
	flex first.l

llist.o: lib/llist.c
	$(CC) -c -g lib/llist.c

plist.o: lib/plist.c
	$(CC) -c -g lib/plist.c

rdparser.o: rdparser.c
	$(CC) -c -g rdparser.c

states: flex_states lex.yy.c
	$(CC) -g lex.yy.c -ll -o bin/states

flex_states:
	flex states.l

basic: flex_basic lex.yy.c
	$(CC) -g lex.yy.c -ll -o bin/basic

flex_basic:
	flex basic.l

test: first
	./bin/first < ./tests/pass0.txt
	./bin/first < ./tests/pass1.txt
	./bin/first < ./tests/pass2.txt
	./bin/first < ./tests/pass3.txt
	./bin/first < ./tests/pass4.txt

clean:
	rm lex.yy.c *.o
