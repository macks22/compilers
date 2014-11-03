uncool:	lex.yy.c uncool.tab.c
	gcc -g -o uncool lex.yy.c uncool.tab.c -ly -lfl

lex.yy.c:	uncool.l
	flex uncool.l

uncool.tab.c:	uncool.y
	bison -vd uncool.y

clean:	
	rm -f lex.yy.c uncool.tab.* uncool.output

realclean:
	rm -f lex.yy.c uncool.tab.* uncool.output uncool
