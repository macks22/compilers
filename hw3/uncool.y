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

program     :    program class
            |    class
            ;

class       :    CLASS_T TYPE '{' feature_list '}'
                    {/* Class declaration
                      * New type being created.
                      */
                    }
            ;

feature_list    :    feature_list feature ';'
                |
                ;

feature     :    ID '(' formal_list ')' ':' typename '{' expr_list  '}'
                    {/* Method declaration with 1+ params.
                      */
                    }
            |    ID '(' ')' ':' typename '{' expr_list '}'
                    {/* Method declaration with 0 params.
                      */
                    }
            |    ID ':' typename
                    {/* Attribute declaration, no assignment.
                      */
                    }
            |    ID ':' typename ASSIGN simple_constant
                    {/* Attribute declaration, assignment to int or bool.
                      */
                    }
            |    ID ':' STRING_T ASSIGN STRING_CONST
                    {/* Attribute declaration, assignment to string.
                      */
                    }
            |    ID ':' INT_T '[' ']'
                    {/* Attribute declaration for int array.
                      */
                    }
            ;

typename    :    INT_T
            |    BOOL_T
            |    STRING_T
            |    TYPE
            ;

simple_constant :    INT_CONST
                        {/* Return type int.
                          */
                        }
                |    TRUE_T
                        {/* Return type bool.
                          */
                        }
                |    FALSE_T
                        {/* Return type bool.
                          */
                        }
                ;

formal_list     :    formal_list ',' formal
                |    formal
                ;

formal      :    ID ':' typename
                    {/* Declare a new attribute.
                      * Create new entry in current scope.
                      * Get type from typename expression and include.
                      */
                    }
            |    ID ':' INT_T '[' ']'
                    {/* Declare a new int array.
                      * Create new entry in current scope.
                      */
                    }
            ;

expr        :    ID ASSIGN expr
                    {/* Assignment to attribute.
                      * return val of expr must be same type as ID
                      */
                    }
            |    ID '[' expr ']' ASSIGN expr
                    {/* Assignment to int array
                      * First expr must return int type.
                      * Second expr must return int type. 
                      */
                    }
            |    ID '.' ID'(' ')'
                    {/* Method call using obj name prefix.
                      * Look up object with first ID to get class scope.
                      * Look up method in class to get type and arg count.
                      * If arg count not equal to 0, raise error.
                      */
                    }
            |    ID '.' ID'(' actual_list ')'
                    {/* Method call using obj name prefix.
                      * Look up object with first ID to get class scope.
                      * Look up method in class scope to get type & arg count.
                      * Figure out size of actual_list & compare w arg count.
                      */
                    }
            |    ID '(' ')'
                    {/* Method call w/o obj name prefix.
                      * Look up ID in current scope. If not present, raise.
                      * If arg count not 0, raise.
                      */
                    }
            |    ID '(' actual_list ')'
                    {/* Method call w/o obj name prefix.
                      * Look up ID in current scope. If not present, raise.
                      * Figure out size of actual_list & compare w arg count.
                      */
                    }
            |    IN_INT '(' ')'
                    {/* Request int from user.
                      * Returns an int.
                      */
                    }
            |    OUT_STRING '(' expr ')'
                    {/* Print out a string.
                      * expr must return a string constant
                      * OUT_STRING returns an int.
                      */
                    }
            |    OUT_INT '(' expr ')'
                    {/* Output an int.
                      * expr must be an int.
                      * Returns an int.
                      */
                    }
            |    ID
                    {/* Simple ID reference.
                      * Look up in scope stack.
                      * If not present, raise.
                      */
                    }
            |    ID '[' expr ']'
                    {/* Simple int array reference.
                      * First look up ID in scope stack.
                      * Then make sure expr returns an int.
                      */
                    }
            |    IF_T expr THEN_T expr ELSE_T expr FI_T
                    {/* Conditional.
                      * First expr must be bool.
                      * Second and Third expr types must match.
                      */
                    }
            |    WHILE_T expr  LOOP_T expr POOL_T
                    {/* Loop.
                      * First expr must be bool.
                      * Second expr is return type of loop.
                      */
                    }
            |    '{' expr_list '}'
                    {/* Series of expr statements.
                      * Return type is return type of last expr.
                      */
                    }
            |    LET_T  formal_list  IN_T expr TEL_T
                    {/* Let statement.
                      * Create new scope to hold formal_list attributes.
                      * These can ONLY be attributes - no methods or classes.
                      * The return type is the return type of expr.
                      */
                    }
            |    NEW_T TYPE '(' ')'
                    {/* Create a new object of class TYPE.
                      * Simply look up class in global scope to ensure exists.
                      */
                    }
            |    NEW_T TYPE '(' actual_list ')'
                    {/* Create new object of class TYPE using init method.
                      * First look up class in global scope to ensure exists.
                      * Next look up init method to make sure it exists.
                      * If found, get arg count.
                      * Compare arg count to actual_list size.
                      * Raise if different.
                      */
                    }
            |    NEW_T INT_T '[' expr ']'
                    {/* Create a new int array.
                      * Ensure expr returns an int.
                      */
                    }
            |    ISVOID_T expr
                    {/* Returns bool and can take any expr.
                      */
                    }
            |    expr '+' expr
                    {/* ADD.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                    }
            |    expr '-' expr
                    {/* MINUS.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                    }
            |    expr '*' expr
                    {/* TIMES.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                    }
            |    '~' expr  %prec UC
                    {/* UNIMINUS.
                      * expr must be int.
                      * Returns an int.
                      */
                    }
            |    NOT_T expr  %prec UM
                    {/* NOT.
                      * expr must be bool.
                      * Returns a bool.
                      */
                    }
            |    expr NE expr
                    {/* NOT EQUAL.
                      * The first expr can have any type.
                      * The second must match the first.
                      * Returns a bool.
                      */
                    }
            |    expr GT expr
                    {/* GREATER THAN.
                      * Both expr must return int.
                      * Returns a bool.
                      */
                    }
            |    expr GE expr
                    {/* GREATER THAN OR EQUAL TO.
                      * Both expr must return int.
                      * Returns a bool.
                      */
                    }
            |    expr LT expr
                    {/* LESS THAN.
                      * Both expr must return int.
                      * Returns a bool.
                      */
                    }
            |    expr LE expr
                    {/* LESS THAN OR EQUAL TO.
                      * Both expr must return int.
                      * Returns a bool.
                      */
                    }
            |    expr EQ expr
                    {/* EQUAL TO.
                      * The first expr can have any type.
                      * The second must match the first.
                      * Returns a bool.
                      */
                    }
            |    '(' expr ')'
                    {/* Used to indicate precedence.
                      * Return type same as expr.
                      */
                    }
            |    TRUE_T
                    {/* Return type bool.
                      */
                    }
            |    FALSE_T
                    {/* Return type bool.
                      */
                    }
            |    INT_CONST
                    {/* Return type int.
                      */
                    }
            |    STRING_CONST
                    {/* Return type string.
                      */
                    }
            ;

actual_list :    actual_list ',' expr
                    {/* Need to count the number of expr stmts when
                      * this shows up in method declarations/calls.
                      * Occurences in let statements need no special
                      * consideration.
                      */
                    }
            |    expr
                    {/* This would indicate final increment for param count.
                      * in method declarations/calls.
                      * Occurences in let statements need no special
                      * consideration.
                      */
                    }
            ;

expr_list   :    expr_list ';' expr
            |    expr
                    {/* This ends up being the final return type.
                      */
                    }
            ;

%%

main(int argc, char **argv) {
   yyparse();
}

yyerror(char *s) {
   printf("Line %d: %s",linect, s);
}
