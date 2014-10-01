all: first

first: flex lex.yy.c rdparser.c rdparser.h tokens.h
	gcc -g rdparser.c lex.yy.c -ll -o bin/first

flex:
	flex first.l

states: flex_states lex.yy.c
	gcc -g lex.yy.c -ll -o bin/states

flex_states:
	flex states.l

basic: flex_basic lex.yy.c
	gcc -g lex.yy.c -ll -o bin/basic

flex_basic:
	flex basic.l

test: first
	./bin/first < ./tests/test0.txt
	./bin/first < ./tests/test1.txt
	./bin/first < ./tests/test2.txt
	./bin/first < ./tests/test3.txt
	./bin/first < ./tests/test4.txt

clean:
	rm lex.yy.c
