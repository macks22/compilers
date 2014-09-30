mtest: log.c unittest.c matrix.c matrix-test.c
	gcc -g log.c unittest.c matrix.c matrix-test.c -o mtest

test: mtest
	./mtest

matexp: matrix-exp.c
	gcc matrix-exp.c -o matexp
