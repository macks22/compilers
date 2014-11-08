all: symtable scope global stack lib

lib: stack lib.c lib-test.c
	gcc -g symtable.c scope.c global.c scope_stack.c lib.c lib-test.c -o lib

stack: scope scope_stack.c scope-stack-test.c
	gcc -g symtable.c scope.c global.c scope_stack.c scope-stack-test.c -o stack

global: scope global.c global-test.c
	gcc -g symtable.c scope.c global.c global-test.c -o global

scope: symtable scope.c scope-test.c
	gcc -g symtable.c scope.c scope-test.c -o scope

symtable: symtable.c symtable-test.c
	gcc -g symtable.c symtable-test.c -o symtable

run:
	./symtable
	./scope
	./global
	./stack
