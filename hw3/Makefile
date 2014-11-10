uncool:	lex.yy.c uncool.tab.c core
	gcc -g -o uncool lex.yy.c uncool.tab.c lib/symtable.c lib/scope.c lib/global.c lib/scope_stack.c lib/core.c -ly -lfl

core: scope lib/core.c

scope: lib/symtable.c lib/scope.c lib/global.c lib/scope_stack.c

lex.yy.c:	uncool.l
	flex uncool.l

uncool.tab.c:	uncool.y
	bison -vd uncool.y

testvalid: uncool
	./uncool < test/valid/test0.uc
	./uncool < test/valid/test1.uc
	./uncool < test/valid/test2.uc
	./uncool < test/valid/test3.uc
	./uncool < test/valid/test4.uc
	./uncool < test/valid/test5.uc
	./uncool < test/valid/test6.uc
	./uncool < test/valid/test7.uc
	./uncool < test/valid/sort.uc

testinvalid: uncool
	./uncool < test/errors/scope_error1.uc
	./uncool < test/errors/scope_error2.uc
	./uncool < test/errors/type_error1.uc
	./uncool < test/errors/type_error2.uc
	./uncool < test/errors/type_error3.uc
	./uncool < test/errors/type_error4.uc

clean:	
	rm -f lex.yy.c uncool.tab.* uncool.output

realclean:
	rm -f lex.yy.c uncool.tab.* uncool.output uncool
