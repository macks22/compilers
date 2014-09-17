all: vec_test hashtest

vec_test: vector.c vector-usage.c
	gcc vector.c vector-usage.c -o vec_test

hashtest: hash.c hash-test.c
	gcc hash-test.c hash.c -o hashtest
