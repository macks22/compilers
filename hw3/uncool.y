%{
#include <stdio.h>
#include <stdlib.h>

extern int linect;


%}

%token CLASS_T INT_T BOOL_T STRING_T IN_T TEL_T
%token THEN_T ELSE_T FI_T LOOP_T POOL_T
%token NEW_T ISVOID_T LE LT GT GE NE EQ NOT_T
%token OUT_STRING OUT_INT IN_INT
%token TRUE_T FALSE_T INT_CONST LET_T IF_T WHILE_T
%token STRING_CONST
%token TYPE
%token ID
%token ASSIGN

%right ASSIGN
%nonassoc GE GT NE LT LE EQ
%right UC
%right UM
%left '+' '-'
%left '*'

%%

program 	:	program class
		|	class
		;

class		:	CLASS_T TYPE '{' feature_list '}'
		;

feature_list	:	feature_list feature ';'
		|
		;

feature		:	ID '( ' formal_list ')' ':' typename '{' expr_list  '}'	
		|	ID '( ' ')' ':' typename '{' expr_list  '}'	
 		| 	ID ':' typename 
 		| 	ID ':' typename ASSIGN simple_constant 
 		| 	ID ':' STRING_T ASSIGN STRING_CONST 
 	 	| 	ID ':' INT_T '[' ']'  
		;

typename	:	INT_T
		|	BOOL_T
		|	STRING_T
		|	TYPE
		;

simple_constant	:	INT_CONST
		|	TRUE_T
		|	FALSE_T
		;

formal_list	:	formal_list ',' formal
		|	formal
		;

formal		:	ID ':' typename 
 	 	| 	ID ':' INT_T '[' ']'  	
		;

expr		:	ID ASSIGN  expr	
 	 	|  	ID '[' expr ']'  ASSIGN  expr 	
 		| 	ID '.' ID'(' ')'	
 		| 	ID '.' ID'(' actual_list ')'	
 		| 	ID '(' ')'	
 		| 	ID '(' actual_list ')'	
		|	IN_INT '(' ')'
		|	OUT_STRING '(' expr ')'
		|	OUT_INT '(' expr ')'
		|	ID
		|	ID '[' expr ']'
 		| 	IF_T expr THEN_T expr ELSE_T expr FI_T 
 		| 	WHILE_T expr  LOOP_T expr POOL_T 
 		| 	'{'    expr_list '}'	
		| 	LET_T  formal_list  IN_T expr TEL_T 	
 		| 	NEW_T TYPE '(' ')'	
 		| 	NEW_T TYPE '(' actual_list ')'	
 	 	|  	NEW_T INT_T '[' expr ']' 	
 		| 	ISVOID_T expr	
 		| 	expr  '+' expr	
 		| 	expr  '-' expr	
 		| 	expr  '*' expr	
 		| 	'~' expr  %prec UC	
		|	NOT_T expr  %prec UM
 		| 	expr NE expr	
 		| 	expr GT expr	
 		| 	expr GE expr	
 		| 	expr LT expr	
 		| 	expr LE expr	
 		| 	expr EQ expr	
		|	'(' expr ')'
 		|	TRUE_T 
 		|	FALSE_T 
 		|	INT_CONST	
		|	STRING_CONST
		;

actual_list	:	actual_list ',' expr
		|	expr
		;

expr_list	:	expr_list ';' expr
		|	expr 
		;


%%

main(int argc, char **argv) {
   yyparse();
}

yyerror(char *s) {
   printf("Line %d: %s",linect, s);
}

