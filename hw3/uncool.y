%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lib/errors.h"
#include "lib/core.h"

#define INT_ARR_T 120

void error(int errtoken, ...);
int wdeclare_attribute(int type);
int wdeclare_method(int type, int argcount);

extern int linect;
extern char *identifier;

int cflag, flag;
ScopeStack *stack;

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

class       :    CLASS_T TYPE
                    {/* Class declaration
                      * New type being created.
                      */
                      cflag = begin_class_declaration(stack, identifier);
                      if (cflag == CLASS_DECL_INSIDE_CLASS_DECL) {
                          error(cflag, current_class_name(stack));
                      } else if (cflag) {
                          error(cflag);
                      }
                    }
                 '{' feature_list '}'
                    { if (!cflag) {
                          end_class_declaration(stack);
                      }
                    }
            ;

feature_list    :    feature_list feature ';'
                |
                ;

feature     :    ID '(' formal_list ')' ':' typename '{' expr_list  '}'
                    {/* Method declaration with 1+ params.
                      */
                    }
            |    ID '(' ')' ':' typename
                    {/* Method declaration with 0 params.
                      */
                      flag = wdeclare_method($5, 0);
                    }
                 '{' expr_list '}'
                    {/* Method declaration with 0 params.
                      */
                      if ($5 != $8) {
                          error(METHOD_BODY_HAS_CONFLICTING_TYPE, $5, $8);
                      }
                    }
            |    ID ':' typename
                    {/* Attribute declaration, no assignment.
                      */
                      flag = wdeclare_attribute($3);
                    }
            |    ID ':' typename
                    {/* Attribute declaration, assignment to int or bool. */
                      flag = wdeclare_attribute($3);
                    }
                 ASSIGN simple_constant
                    {/* Assign to the attribute just created. */
                      if (!flag) {
                          // TODO: make sure simple_constant type matches
                      }
                    }
            |    ID ':' STRING_T
                    {/* Attribute declaration, assignment to string. */
                      flag = wdeclare_attribute($3);
                    }
                 ASSIGN STRING_CONST
                    {/* Assign string constant to attribute just created. */
                      if (!flag) {
                          // nothing to do here; string_const always string_t
                      }
                    }
            |    ID ':' INT_T '[' ']'
                    {/* Attribute declaration for int array. */
                      flag = wdeclare_attribute(INT_ARR_T);
                    }
            ;

typename    :    INT_T { $$ = INT_T; }
            |    BOOL_T { $$ = BOOL_T; }
            |    STRING_T { $$ = STRING_T; }
            |    TYPE
                    { $$ = $1; }
            ;

simple_constant :    INT_CONST { $$ = INT_T; }
                |    TRUE_T { $$ = BOOL_T; }
                |    FALSE_T { $$ = BOOL_T; }
                ;

formal_list     :    formal_list ',' formal
                        {/* Return parameter count. */
                            $$ = $1 + $3;
                        }
                |    formal
                        {/* Return parameter count. */
                            $$ = 1;
                        }
                ;

formal      :    ID ':' typename
                    {/* Attribute declaration, assignment to int or bool. */
                      flag = wdeclare_attribute($3);
                    }
            |    ID ':' INT_T '[' ']'
                    {/* Attribute declaration for int array. */
                      flag = wdeclare_attribute(INT_ARR_T);
                    }
            ;

expr        :    ID ASSIGN expr
                    {/* Assignment to attribute.
                      * return val of expr must be same type as ID
                      */
                      $$ = $3;
                    }
            |    ID '[' expr ']' ASSIGN expr
                    {/* Assignment to int array
                      * First expr must return int type.
                      * Second expr must return int type.
                      */
                      $$ = $6;
                    }
            |    ID '.' ID '(' ')'
                    {/* Method call using obj name prefix.
                      * Look up object with first ID to get class scope.
                      * Look up method in class to get type and arg count.
                      * If arg count not equal to 0, raise error.
                      */
                    }
            |    ID '.' ID '(' actual_list ')'
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
                      $$ = INT_T;
                    }
            |    OUT_INT '(' expr ')'
                    {/* Output an int.
                      * expr must be an int.
                      * Returns an int.
                      */
                      $$ = INT_T;
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
                      $$ = $2;
                    }
            |    LET_T formal_list IN_T expr TEL_T
                    {/* Let statement.
                      * Create new scope to hold formal_list attributes.
                      * These can ONLY be attributes - no methods or classes.
                      * The return type is the return type of expr.
                      */
                      $$ = $5;
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
                      * this shows up in method calls.
                      * Does not show up in declarations.
                      * Occurences in let statements need no special consideration.
                      */
                    }
            |    expr
                    {/* This would indicate single parameter for param count
                      * in method calls.
                      * Does not show up in declarations.
                      * Occurences in let statements need no special consideration.
                      */
                    }
            ;

expr_list   :    expr_list ';' expr
                    { $$ = $3; }
            |    expr
                    { $$ = $1; }
            ;

%%

main(int argc, char **argv) {
    stack = scope_stack_create();
    yyparse();
    print_scope_stack(stack);
}

yyerror(char *s) {
   printf("Line %d: %s",linect, s);
}

int wdeclare_attribute(int type)
{   /* Wrapper to simplify args and error handling.
     * Relies on global identifier and stack.
     */
    flag = declare_attribute(stack, identifier, type);
    if (flag) error(flag);
    return flag;
}

int wdeclare_method(int type, int argcount)
{   /* Wrapper to simplify args and error handling.
     * Relies on global identifier and stack.
     */
    flag = declare_method(stack, identifier, type, argcount);
    if (flag) error(flag);
    return flag;
}

void
error(int errtoken, ...)
{
    int print_lineno = 1;
    va_list argp;
    va_start(argp, errtoken);

    if (errtoken == NO_MAIN_CLASS) {
        printf("no Main class found\n");
        print_lineno = 0;
    } else if (errtoken == NO_MAIN_METHOD) {
        printf("no main method found in Main class\n");
        print_lineno = 0;
    }

    if (errtoken == DUPLICATE_CLASS) {
        printf("duplicate class declaration [name: %s]", identifier);
    } else if (errtoken == DUPLICATE_ATTRIBUTE) {
        printf("duplicate attribute declaration [name: %s]", identifier);
    } else if (errtoken == DUPLICATE_METHOD) {
        printf("duplicate method declaration [name: %s']", identifier);
    } else if (errtoken == METHOD_DECL_OUTSIDE_CLASS_SCOPE) {
        printf("method declaration outside class scope [name: %s]", identifier);
    } else if (errtoken == ATTRIBUTE_DECL_IN_GLOBAL_SCOPE) {
        printf("attribute declaration in global scope [name: %s]", identifier);
    } else if (errtoken == CLASS_DECL_INSIDE_CLASS_DECL) {
        printf("class declaration inside declaration of class %s [name: %s]",
               va_arg(argp, char *), identifier);
    } else if (errtoken == NO_SUCH_CLASS) {
        printf("no such class found [name: %s]", identifier);
    } else if (errtoken == NO_SUCH_ATTRIBUTE) {
        printf("no such attribute declared [name: %s]", identifier);
    } else if (errtoken == NO_SUCH_METHOD) {
        printf("no such method for class [class: %s][method: %s]",
               va_arg(argp, char *), identifier);
    } else if (errtoken == METHOD_BODY_HAS_CONFLICTING_TYPE) {
        printf("method body has conflicting type [method: %s]", identifier);
        printf("[declared type: %d][body type: %d]",
               va_arg(argp, int), va_arg(argp, int));
    }

    va_end(argp);
    if (print_lineno) {
        printf("[line %d]\n", linect);
    }
}
