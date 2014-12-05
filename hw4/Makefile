uncool:	lex.yy.c uncool.tab.c core
	gcc -g -o uncool lex.yy.c uncool.tab.c lib/symtable.c lib/scope.c lib/global.c lib/scope_stack.c lib/core.c gen.c registers.c -ly -lfl

core: scope lib/core.c gen.c registers.c

scope: lib/symtable.c lib/scope.c lib/global.c lib/scope_stack.c

lex.yy.c:	uncool.l
	flex uncool.l

uncool.tab.c:	uncool.y
	bison -vd uncool.y

work: uncool
	./uncool < test/work.uc | tee test.s
	gcc -g -m32 test.s

test: uncool
	./uncool < test/test0.uc > test0.s
	./uncool < test/test1.uc > test1.s
	./uncool < test/test2.uc > test2.s
	./uncool < test/test3.uc > test3.s
	./uncool < test/test4.uc > test4.s
	./uncool < test/test5.uc > test5.s
	./uncool < test/test6.uc > test6.s
	./uncool < test/test7.uc > test7.s
	./uncool < test/sort.uc  > sort.s

compile: uncool test
	gcc -g -m32 test0.s -o test0.out
	gcc -g -m32 test1.s -o test1.out
	gcc -g -m32 test2.s -o test2.out
	gcc -g -m32 test3.s -o test3.out
	gcc -g -m32 test4.s -o test4.out
	gcc -g -m32 test5.s -o test5.out
	gcc -g -m32 test6.s -o test6.out
	gcc -g -m32 test7.s -o test7.out
	gcc -g -m32 sort.s  -o sort.out	

clean:	
	rm -f lex.yy.c uncool.tab.* uncool.output

realclean:
	rm -f lex.yy.c uncool.tab.* uncool.output uncool
