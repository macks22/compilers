all: plist lltest

plist: llist.h llist.c plist.h plist.c plist-test.c
	gcc -g llist.c plist.c plist-test.c -o plist

lltest: llist.h llist.c llist-test.c
	gcc -g llist.c llist-test.c -o lltest

test: plist lltest
	./plist
	./lltest
	rm plist lltest
