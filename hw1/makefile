all: lexer

lexer: flex lex.yy.c
	gcc -g lex.yy.c lib/vector.c lib/hash.c -ll -o bin/lexer

flex:
	flex lexer.l

test:
	./bin/lexer < ./tests/test0.txt
	./bin/lexer < ./tests/test1.txt
	./bin/lexer < ./tests/test2.txt
	./bin/lexer < ./tests/test3.txt

clean:
	rm lex.yy.c
