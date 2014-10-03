lltest: llist.h llist.c llist-test.c
	gcc -g llist.c llist-test.c -o lltest

darrtest: darray.c darray.h darray-test.c
	gcc -g darray.c darray-test.c -o darrtest

mtest: log.c unittest.c matrix.c matrix-test.c
	gcc -g log.c unittest.c matrix.c matrix-test.c -o mtest

test: mtest
	./mtest

matexp: matrix-exp.c
	gcc matrix-exp.c -o matexp
