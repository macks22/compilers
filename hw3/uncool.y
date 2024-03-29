%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include "lib/errors.h"
#include "lib/core.h"
#include "logging.h"

void error(int errtoken, ...);
int wdeclare_attribute(char *name, int type);
int wdeclare_method(char *name, int type, int argcount);
void wend_method(int flag);

char *containing_class_name();
int check_array_index(int type);
int check_method_types(char *name, int type1, int type2);
int type_check_attr(char *name, int correct_type, int assign_type);
int type_check_int_arr_assign(char *name, int assign_type);
int get_attribute_type(char *name);
char *type_name_from_token(int token);
int check_method_ref(char *class_name, char *method_name, int argcount);
int make_new_class(char *class_name, int argcount);

extern int verbose;
extern int linect;

int num_errors;

char *cname;
int cflag, dflag, flag, typetoken;
ScopeStack *stack;
Symbol *method, attr;

%}

%token CLASS_T INT_T BOOL_T STRING_T IN_T TEL_T INT_ARR_T VOID_T
%token THEN_T ELSE_T FI_T LOOP_T POOL_T
%token NEW_T ISVOID_T SELF_T LE LT GT GE NE EQ NOT_T
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

%union
{
    int type;
    char *str;
}

%type <type> CLASS_T INT_T BOOL_T STRING_T IN_T TEL_T INT_ARR_T VOID_T
%type <type> THEN_T ELSE_T FI_T LOOP_T POOL_T
%type <type> NEW_T ISVOID_T SELF_T LE LT GT GE NE EQ NOT_T
%type <type> OUT_STRING OUT_INT IN_INT
%type <type> TRUE_T FALSE_T INT_CONST LET_T IF_T WHILE_T
%type <type> STRING_CONST
%type <type> ASSIGN
%type <str> ID TYPE

%type <type> expr expr_list formal formal_list simple_constant typename
%type <type> actual_list

%%


program     :    program class
            |    class
            ;

class       :    CLASS_T TYPE
                    {/* Class declaration
                      * New type being created.
                      */
                      cflag = begin_class_declaration(stack, $2);
                      if (cflag == CLASS_DECL_INSIDE_CLASS_DECL) {
                          error(cflag, $2, $2);
                      } else if (cflag) {
                          error(cflag, $2);
                      } else {
                          log_info("created new class: %s\n", $2);
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

feature     :    ID '('
                    {/* Method declaration with 1+ params. */
                        if (in_method_scope(stack)) {
                            error(METHOD_DECL_INSIDE_METHOD_DECL, $1);
                        } else if (!in_class_scope(stack)) {
                            error(METHOD_DECL_OUTSIDE_CLASS_SCOPE, $1);
                        } else if (method_exists(stack->local, $1)) {
                            error(DUPLICATE_METHOD, $1);
                        } else {  // Houston, we have lift off
                            enter_scope(stack, METHOD_SCOPE, $1);
                        }

                    }
                 formal_list ')' ':' typename
                    { log_info("begin method decl '%s' of type %s & argcnt %d\n",
                               $1, type_name_from_token($7), $4);
                      scope_add_method(stack->scopes[stack->size-2], $1, $7, $4);
                    }
                 '{' expr_list '}'
                    {/* type check declaration and return type of expr_list */
                      wend_method(dflag);
                      check_method_types($1, $7, $10);
                    }
            |    ID '(' ')' ':' typename
                    {/* Method declaration with 0 params. */
                      dflag = wdeclare_method($1, $5, 0);
                    }
                 '{' expr_list '}'
                    {/* type check declaration and return type of expr_list */
                      wend_method(dflag);
                      check_method_types($1, $5, $8);
                    }
            |    ID ':' typename
                    {/* Attribute declaration, no assignment. */
                      flag = wdeclare_attribute($1, $3);
                    }
            |    ID ':' typename
                    {/* Attribute declaration, assignment to int or bool. */
                      flag = wdeclare_attribute($1, $3);
                    }
                 ASSIGN simple_constant
                    {/* Assign to the attribute just created. */
                      if (!flag) {
                          type_check_attr($1, $3, $6);
                      }
                    }
            |    ID ':' STRING_T
                    {/* Attribute declaration, assignment to string. */
                      flag = wdeclare_attribute($1, STRING_T);
                    }
                 ASSIGN STRING_CONST
                    {/* Assign string constant to attribute just created. */
                      if (!flag) {
                          // nothing to do here; string_const always string_t
                      }
                    }
            |    ID ':' INT_T '[' ']'
                    {/* Attribute declaration for int array. */
                      flag = wdeclare_attribute($1, INT_ARR_T);
                    }
            ;

typename    :    INT_T { $$ = INT_T; }
            |    BOOL_T { $$ = BOOL_T; }
            |    STRING_T { $$ = STRING_T; }
            |    TYPE
                    {/* At this point, the class will have been defined. */
                      Scope *class = lookup_class(stack, $1);
                      if (class == NULL) {
                          error(NO_SUCH_CLASS, $1);
                          $$ = INVALID_TYPE;
                      } else {
                          $$ = class->typetoken;
                      }
                    }
            ;

simple_constant :    INT_CONST { $$ = INT_T; }
                |    TRUE_T { $$ = BOOL_T; }
                |    FALSE_T { $$ = BOOL_T; }
                ;

formal_list     :    formal_list ',' formal
                        {/* Return parameter count. */
                            $$ = $1 + 1;
                        }
                |    formal
                        {/* Return parameter count. */
                            $$ = 1;
                        }
                ;

formal      :    ID ':' typename
                    {/* Attribute declaration, assignment to int or bool. */
                      flag = wdeclare_attribute($1, $3);
                    }
            |    ID ':' INT_T '[' ']'
                    {/* Attribute declaration for int array. */
                      flag = wdeclare_attribute($1, INT_ARR_T);
                    }
            ;

expr        :    ID ASSIGN expr
                    {/* Assignment to attribute.
                      * return val of expr must be same type as ID
                      */
                      flag = get_attribute_type($1);
                      type_check_attr($1, flag, $3);
                      $$ = $3;
                    }
            |    ID '[' expr ']' ASSIGN expr
                    {/* Assignment to int array
                      * First expr must return int type.
                      * Second expr must return int type.
                      */
                      flag = get_attribute_type($1);
                      if (flag != INT_ARR_T) {
                          error(INDEXING_NON_ARRAY, $1);
                      }
                      check_array_index($3);
                      type_check_int_arr_assign($1, $6);
                      $$ = $6;
                    }
            |    ID '.' ID '(' ')'
                    {/* Method call using obj name prefix.
                      * Look up object with first ID to get class scope.
                      * Look up method in class to get type and arg count.
                      * If arg count not equal to 0, raise error.
                      */
                      typetoken = get_attribute_type($1);
                      cname = type_name_from_token(typetoken);
                      $$ = check_method_ref(cname, $3, 0);
                    }
            |    ID '.' ID '(' actual_list ')'
                    {/* Method call using obj name prefix.
                      * Look up object with first ID to get class scope.
                      * Look up method in class scope to get type & arg count.
                      * Figure out size of actual_list & compare w arg count.
                      */
                      typetoken = get_attribute_type($1);
                      cname = type_name_from_token(typetoken);
                      $$ = check_method_ref(cname, $3, $5);
                    }
            |    ID '(' ')'
                    {/* Method call w/o obj name prefix.
                      * Look up ID in current scope. If not present, raise.
                      * If arg count not 0, raise.
                      */
                      cname = containing_class_name(stack);
                      if (cname == NULL) {
                          error(SELF_REFERENCE_OUTSIDE_CLASS);
                          $$ = INVALID_TYPE;
                      } else {
                          $$ = check_method_ref(cname, $1, 0);
                      }
                    }
            |    ID '(' actual_list ')'
                    {/* Method call w/o obj name prefix.
                      * Look up ID in current scope. If not present, raise.
                      * Figure out size of actual_list & compare w arg count.
                      */
                      cname = containing_class_name(stack);
                      log_debug("containing class name for 'self' ref: %s\n",
                                cname);
                      if (cname == NULL) {
                          error(SELF_REFERENCE_OUTSIDE_CLASS);
                          $$ = INVALID_TYPE;
                      } else {
                          log_info("%s called with %d argument(s)\n", $1, $3);
                          $$ = check_method_ref(cname, $1, $3);
                      }
                    }
            |    IN_INT '(' ')'
                    {/* Request int from user.
                      * Returns an int.
                      */
                      $$ = INT_T;
                    }
            |    OUT_STRING '(' expr ')'
                    {/* Print out a string.
                      * expr must return a string constant
                      * OUT_STRING returns an int.
                      */
                      $$ = INT_T;
                      if ($3 != STRING_T) {
                          error(OUT_STRING_EXPECTS_STRING, $3);
                      }
                    }
            |    OUT_INT '(' expr ')'
                    {/* Output an int.
                      * expr must be an int. Returns an int.
                      */
                      $$ = INT_T;
                      if ($3 != INT_T) {
                          error(OUT_INT_EXPECTS_INT, $3);
                      }
                    }
            |    ID
                    {/* Simple ID reference.
                      * Look up in scope stack.
                      * If not present, raise.
                      */
                      flag = get_attribute_type($1);
                      $$ = flag;  // whether valid or invalid, this works
                    }
            |    ID '[' expr ']'
                    {/* Simple int array reference.
                      * First look up ID in scope stack.
                      * Then make sure expr returns an int.
                      * Return type is always int.
                      */
                      flag = get_attribute_type($1);
                      if (flag != INT_ARR_T) {
                          error(INDEXING_NON_ARRAY, $1);
                      }
                      if (flag >= 0) {  // valid reference
                          check_array_index($3);
                      }
                      $$ = INT_T;
                    }
            |    IF_T expr THEN_T expr ELSE_T expr FI_T
                    {/* Conditional.
                      * First expr must be bool.
                      * Second and Third expr types must match, and this
                      * is the return type.
                      */
                      if ($2 != BOOL_T) {
                          error(PREDICATE_NOT_BOOL, "if");
                          $$ = INVALID_TYPE;
                      } else if ($4 != $6) {
                          error(CONDITIONAL_BRANCH_TYPES_DIFFER, $4, $6);
                          $$ = $4;
                      } else {
                          $$ = $4;
                      }
                    }
            |    WHILE_T expr
                    {/* Loop.
                      * First expr must be bool.
                      * Return type is always Int.
                      */
                      if ($2 != BOOL_T) {
                          error(PREDICATE_NOT_BOOL, "while");
                      }
                    }
                 LOOP_T expr POOL_T
                    { $$ = INT_T; }
            |    '{' expr_list '}'
                    {/* Series of expr statements.
                      * Return type is return type of last expr.
                      */
                      $$ = $2;
                    }
            |    LET_T
                    {/* Let statement.
                      * Create new scope to hold formal_list attributes.
                      */
                      enter_let_scope(stack);
                      log_info("entering let scope");
                    }
                 formal_list IN_T expr TEL_T
                    {/* These can ONLY be attributes - no methods or classes.
                      * The return type is the return type of expr.
                      */
                      $$ = $5;
                      if (verbose == LOGGING_LEVEL_DEBUG) {
                          print_let_scope(stack->global, stack->local);
                      }
                      exit_scope(stack);
                      log_info("exiting let scope");
                    }
            |    NEW_T TYPE '(' ')'
                    {/* Create a new object of class TYPE.
                      * Simply look up class in global scope to ensure exists.
                      */
                      $$ = make_new_class($2, 0);
                    }
            |    NEW_T TYPE '(' actual_list ')'
                    {/* Create new object of class TYPE using init method.
                      * First look up class in global scope to ensure exists.
                      * Next look up init method to make sure it exists.
                      * If found, get arg count.
                      * Compare arg count to actual_list size.
                      * Raise if different.
                      */
                      $$ =make_new_class($2, $4);
                    }
            |    NEW_T INT_T '[' expr ']'
                    {/* Create a new int array.
                      * Ensure expr returns an int.
                      */
                      check_array_index($4);
                      if ($4 != INT_T) {
                          error(ARRAY_SIZE_NOT_INT, $4);
                      }
                      $$ = INT_ARR_T;
                    }
            |    ISVOID_T expr
                    {/* Returns bool and can take any expr.
                      */
                      $$ = BOOL_T;
                    }
            |    expr '+' expr
                    {/* ADD.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                      if ($1 != INT_T || $3 != INT_T) {
                          error(EXPECTED_INT_OPERANDS, "+", $1, $3);
                      }
                      $$ = INT_T;
                    }
            |    expr '-' expr
                    {/* MINUS.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                      if ($1 != INT_T || $3 != INT_T) {
                          error(EXPECTED_INT_OPERANDS, "-", $1, $3);
                      }
                      $$ = INT_T;
                    }
            |    expr '*' expr
                    {/* TIMES.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                      if ($1 != INT_T || $3 != INT_T) {
                          error(EXPECTED_INT_OPERANDS, "*", $1, $3);
                      }
                      $$ = INT_T;
                    }
            |    '~' expr  %prec UC
                    {/* UNIMINUS.
                      * expr must be int.
                      * Returns an int.
                      */
                      if ($2 != INT_T) {
                          error(UNIMINUS_EXPR_NOT_INT, $2);
                      }
                      $$ = INT_T;
                    }
            |    NOT_T expr  %prec UM
                    {/* NOT.
                      * expr must be bool. Returns a bool.
                      */
                      if ($2 != BOOL_T) {
                          error(NOT_EXPR_NOT_BOOL, $2);
                      }
                      $$ = BOOL_T;
                    }
            |    expr NE expr
                    {/* NOT EQUAL.
                      * 1st expr can have any type. 2nd must match the first.
                      * Returns a bool.
                      */
                      if ($1 != $3) {
                          error(COMPARISON_OP_TYPE_MISMATCH, $1, $3);
                      }
                      $$ = BOOL_T;
                    }
            |    expr GT expr
                    {/* GREATER THAN.
                      * Both expr must return int. Returns a bool.
                      */
                      if ($1 != INT_T || $3 != INT_T) {
                          error(COMPARISON_OP_TYPES_NOT_INT, $1, $3);
                      }
                      $$ = BOOL_T;
                    }
            |    expr GE expr
                    {/* GREATER THAN OR EQUAL TO.
                      * Both expr must return int. Returns a bool.
                      */
                      if ($1 != INT_T || $3 != INT_T) {
                          error(COMPARISON_OP_TYPES_NOT_INT, $1, $3);
                      }
                      $$ = BOOL_T;
                    }
            |    expr LT expr
                    {/* LESS THAN.
                      * Both expr must return int. Returns a bool.
                      */
                      if ($1 != INT_T || $3 != INT_T) {
                          error(COMPARISON_OP_TYPES_NOT_INT, $1, $3);
                      }
                      $$ = BOOL_T;
                    }
            |    expr LE expr
                    {/* LESS THAN OR EQUAL TO.
                      * Both expr must return int. Returns a bool.
                      */
                      if ($1 != INT_T || $3 != INT_T) {
                          error(COMPARISON_OP_TYPES_NOT_INT, $1, $3);
                      }
                      $$ = BOOL_T;
                    }
            |    expr EQ expr
                    {/* EQUAL TO.
                      * 1st expr can have any type. 2nd must match the first.
                      * Returns a bool.
                      */
                      if ($1 != $3) {
                          error(COMPARISON_OP_TYPE_MISMATCH, $1, $3);
                      }
                      $$ = BOOL_T;
                    }
            |    '(' expr ')'
                    {/* Used to indicate precedence.
                      * Return type same as expr.
                      */
                      $$ = $2;
                    }
            |    TRUE_T
                    {/* Return type bool. */
                      $$ = BOOL_T;
                    }
            |    FALSE_T
                    {/* Return type bool. */
                      $$ = BOOL_T;
                    }
            |    INT_CONST
                    {/* Return type int. */
                      $$ = INT_T;
                    }
            |    STRING_CONST
                    {/* Return type string. */
                      $$ = STRING_T;
                    }
            |    SELF_T
                    {/* Reference to current class. */
                      $$ = (containing_class(stack))->typetoken;
                    }
            ;

actual_list :    actual_list ',' expr
                    {/* Need to count the number of expr stmts when
                      * this shows up in method calls.
                      * Does not show up in declarations.
                      * Occurences in let statements need no special consideration.
                      */
                      $$ = $1 + 1;
                    }
            |    expr
                    {/* This would indicate single parameter for param count
                      * in method calls.
                      * Does not show up in declarations.
                      * Occurences in let statements need no special consideration.
                      */
                      $$ = 1;
                    }
            ;

expr_list   :    expr_list ';' expr
                    { $$ = $3; }
            |    expr
                    { $$ = $1; }
            ;

%%

void
safe_type_create(int token, char *name)
{
    int flag = create_type(stack, token, name);
    if (flag) {
        log_debug("attempt to map token %d to name %s would clobber\n",
                  token, name);
        exit(flag);
    }
    log_info("created new type: %s [token: %d]\n", name, token);
}

main (int argc, char **argv) {
    int flag;
    Scope *class;
    Symbol *method;

    if (argc == 2) {
        if (strcmp(argv[1], "-v") == 0) {
            verbose = LOGGING_LEVEL_INFO;
            printf("continuing with verbose output\n");
        } else if (strcmp(argv[1], "-vv") == 0) {
            verbose = LOGGING_LEVEL_DEBUG;
            printf("continuing with debug level verbose output\n");
        } else {
            verbose = 0;
        }
    }

    num_errors = 0;
    stack = scope_stack_create();

    // create built-in types
    log_info("declaring built-in types\n");
    safe_type_create(INT_T, "Int");
    safe_type_create(STRING_T, "String");
    safe_type_create(BOOL_T, "Bool");
    safe_type_create(INT_ARR_T, "Int[]");
    safe_type_create(VOID_T, "Void");
    log_info("finished type declarations\n");

    yyparse();
    printf("ERRORS FOUND: %d\n", num_errors);

    class = lookup_class(stack, "Main");
    if (class == NULL) {
        error(NO_MAIN_CLASS);
    } else {
        method = lookup_method(stack, "Main", "main");
        if (method == NULL) {
            error(NO_MAIN_METHOD);
        }
    }

    // log end-file scope stack and type info
    if (verbose == LOGGING_LEVEL_DEBUG) {
        print_scope_stack(stack);
        printf("TYPES:\n");
        print_type_map(stack);
    }
    scope_stack_destroy(stack);
    return 0;
}

yyerror(char *s) {
   printf("Line %d: %s",linect, s);
}

int
wdeclare_attribute(char *name, int type)
{   /* Wrapper to simplify args and error handling.
     * Relies on global stack.
     */
    flag = declare_attribute(stack, name, type);
    if (flag) {
        error(flag, name);
    } else {
        log_info("declared attribute '%s' with type: %s\n",
                 name, type_name_from_token(type));
    }
    return flag;
}

int wdeclare_method(char *name, int type, int argcount)
{   /* Wrapper to simplify args and error handling.
     * Relies on global stack.
     */
    flag = begin_method_declaration(stack, name, type, argcount);
    if (flag) {
        error(flag, name);
    } else {
        log_info("begin method decl '%s' with type %s and argcount %d\n", name,
                 type_name_from_token(type), argcount);
    }
    return flag;
}

void
wend_method(int dflag)
{
    log_debug("flag value from method declaration: %d\n", dflag);
    if (!dflag) {
        log_info("end method decl: %s\n", stack->local->name);
        end_method_declaration(stack);
    }
}

int
check_array_index(int type)
{   /* Return 0 if all good, otherwise an error code.
     * The error message is printed by return time.
     */
    if (type != INT_T) {
        error(INDEX_NOT_INT, type);
        return INDEX_NOT_INT;
    }
    return 0;
}

int
check_method_types(char *name, int declared, int returned)
{
    if (declared != returned) {
        error(METHOD_BODY_HAS_CONFLICTING_TYPE, name,
              declared, returned);
        log_debug("declared type token: %d\n", declared);
        log_debug("returned type token: %d\n", returned);
    }
}

int
type_check_attr(char *name, int correct_type, int assign_type)
{   /* Return 0 if mismatch, else 1.
     * Error handling taken care of by return time.
     */

    log_debug("type checking attribute %s\n", name);
    log_debug("compare correct (%s) with assignment type (%s)\n",
              type_name_from_token(correct_type),
              type_name_from_token(assign_type));

    if (correct_type != assign_type) {
        error(CONFLICTING_ATTRIBUTE_TYPE, name, correct_type, assign_type);
        return 1;
    }
    return 0;
}

int
type_check_int_arr_assign(char *name, int assign_type)
{
    log_debug("type checking attribute %s\n", name);
    log_debug("compare correct (%s) with assignment type (%s)\n",
              "Int []", "Int");

    if (assign_type != INT_T) {
        error(CONFLICTING_ATTRIBUTE_TYPE, name, INT_T, assign_type);
    }
}

int
get_attribute_type(char *name)
{
    Symbol *attr = lookup_attribute(stack, name);
    if (attr == NULL) {
        error(NO_SUCH_ATTRIBUTE, name);
        return INVALID_TYPE;
    } else {
        log_info("attribute lookup successful for: %s\n", name);
        return attr->type;
    }
}

char *
type_name_from_token(int token)
{
    if (token < 0) {  // invalid token
        return "NULL";
    } else {
        return type_name(stack, token);
    }
}

int
method_type(char *class_name, char *method_name)
{
    Symbol *method = lookup_method(stack, class_name, method_name);
    if (method == NULL) {
        log_debug("class lookup failed for assigned class type");
        exit(NO_SUCH_CLASS);
    } else {
        return method->type;
    }
}

int
check_method_ref(char *class_name, char *method_name, int argcount)
{   /* Make sure the method exists for the class.
     * Return the type if it does.
     * Otherwise indicate appropriate errors.
     */
    log_debug("checking method argument count\n");
    log_debug("class name: %s\n", class_name);
    log_debug("method name: %s\n", method_name);
    Symbol *method = lookup_method(stack, class_name, method_name);
    if (method == NULL) {
        error(NO_SUCH_METHOD, class_name, method_name);
        return INVALID_TYPE;
    }
    assert(strcmp(method->name, method_name) == 0);
    log_debug("successful lookup for method %s of class %s\n", method->name,
              class_name);
    log_debug("method expects %d arguments\n", method->argcount);

    if (method->argcount != argcount) {
        error(METHOD_INVALID_ARGCOUNT, class_name, method_name,
              method->argcount, argcount);
    }
    return method->type;
}

char *
get_type_name(va_list argp)
{
    int token = va_arg(argp, int);
    if (token < 0) {  // invalid token
        return "NULL";
    } else {
        return type_name(stack, token);
    }
}

char *
containing_class_name()
{
    Scope *class = containing_class(stack);
    if (class == NULL) {
        return NULL;
    }
    return class->name;
}

int
make_new_class(char *name, int argcount)
{
    Scope *class;
    Symbol *method;

    log_info("instantiating new instance of class %s\n", name);
    class = lookup_class(stack, name);
    if (class == NULL) {
        log_info("no class found with name %s; instantiation failed\n", name);
        return INVALID_TYPE;
    } else {
        // look up init method
        log_debug("looking up init method for class %s\n", name);
        method = lookup_method(stack, name, "init");
        if (method == NULL && (argcount > 0)) {
            error(OBJECT_INSTANTIATION_INVALID_ARGCOUNT,
                  name, 0, argcount);
        } else {  // have an init
            log_debug("init method found, argcount should be: %d\n",
                      method->argcount);
            if (method->argcount != argcount) {
                error(OBJECT_INSTANTIATION_INVALID_ARGCOUNT,
                      name, method->argcount, argcount);
            }
        }
        return class->typetoken;
    }
}

void
error(int errtoken, ...)
{
    char *name, *name2, *type1, *type2;
    int t1, t2, t3;
    va_list argp;
    va_start(argp, errtoken);

    num_errors++;
    printf("[LINE %d][ERROR]: ", linect);

    if (errtoken == NO_MAIN_CLASS) {
        printf("no Main class found\n");
        return;
    } else if (errtoken == NO_MAIN_METHOD) {
        printf("no main method found in Main class\n");
        return;
    }

    if (errtoken == DUPLICATE_CLASS) {
        name = va_arg(argp, char *);
        printf("duplicate class declaration \n\t[name: %s]", name);
    } else if (errtoken == DUPLICATE_ATTRIBUTE) {
        name = va_arg(argp, char *);
        printf("duplicate attribute declaration \n\t[name: %s]", name);
    } else if (errtoken == DUPLICATE_METHOD) {
        name = va_arg(argp, char *);
        printf("duplicate method declaration\n\t[name: %s']", name);
    } else if (errtoken == METHOD_DECL_OUTSIDE_CLASS_SCOPE) {
        name = va_arg(argp, char *);
        printf("method declaration outside class scope\n\t[name: %s]", name);
    } else if (errtoken == ATTRIBUTE_DECL_IN_GLOBAL_SCOPE) {
        name = va_arg(argp, char *);
        printf("attribute declaration in global scope\n\t[name: %s]", name);
    } else if (errtoken == CLASS_DECL_INSIDE_CLASS_DECL) {
        name = va_arg(argp, char *);
        name2 = va_arg(argp, char *);
        printf("class declaration inside declaration of class %s\n\t[name: %s]",
               name, name2);
    } else if (errtoken == NO_SUCH_CLASS) {
        name = va_arg(argp, char *);
        printf("invalid type (no such class found)\n\t[name: %s]", name);
    } else if (errtoken == NO_SUCH_ATTRIBUTE) {
        name = va_arg(argp, char *);
        printf("no such attribute declared\n\t[name: %s]", name);
    } else if (errtoken == NO_SUCH_METHOD) {
        name = va_arg(argp, char *);
        name2 = va_arg(argp, char *);
        printf("no such method for class\n\t[class: %s][method: %s]",
               name, name2);
    } else if (errtoken == METHOD_BODY_HAS_CONFLICTING_TYPE) {
        name = va_arg(argp, char *);
        printf("method body has conflicting type\n\t[method: %s]", name);
        type1 = get_type_name(argp);
        type2 = get_type_name(argp);
        printf("[declared: %s][body: %s]", type1, type2);
    } else if (errtoken == PREDICATE_NOT_BOOL) {
        printf("predicate is not boolean");
    } else if (errtoken == CONDITIONAL_BRANCH_TYPES_DIFFER) {
        type1 = get_type_name(argp);
        type2 = get_type_name(argp);
        printf("conditional branch types differ\n\t[1st: %s][2nd: %s]",
               type1, type2);
    } else if (errtoken == INDEX_NOT_INT) {
        printf("attempting to index int array with non-int ");
        type1 = get_type_name(argp);
        printf("\n\t[index type: %s]", type1);
    } else if (errtoken == ARRAY_SIZE_NOT_INT) {
        type1 = get_type_name(argp);
        printf("initial array size is not integer\n\t[type: %s]", type1);
    } else if (errtoken == CONFLICTING_ATTRIBUTE_TYPE) {
        printf("assignment type does not match attribute type");
        name = va_arg(argp, char *);
        type1 = get_type_name(argp);
        type2 = get_type_name(argp);
        printf("\n\t[name: %s][correct type: %s][assignment type: %s]",
               name, type1, type2);
    } else if (errtoken == METHOD_DECL_INSIDE_METHOD_DECL) {
        printf("method declaration inside another method declaration");
        name = va_arg(argp, char *);
        printf("\n\t[name: %s]", name);
    } else if (errtoken == METHOD_INVALID_ARGCOUNT) {
        name = va_arg(argp, char *);
        name2 = va_arg(argp, char *);
        printf("invalid argument count for method\n\t[class: %s][method: %s]",
               name, name2);
        t1 = va_arg(argp, int);
        t2 = va_arg(argp, int);
        printf("[expected: %d][got: %d]", t1, t2);
    } else if (errtoken == INDEXING_NON_ARRAY) {
        name = va_arg(argp, char *);
        printf("indexing non array attribute\n\t[name: %s]", name);
    } else if (errtoken == SELF_REFERENCE_OUTSIDE_CLASS) {
        printf("reference to 'self' outside of class scope");
    } else if (errtoken == OUT_INT_EXPECTS_INT) {
        type1 = get_type_name(argp);
        printf("out_int expects integer argument");
        printf("\n\t[got: %s]", type1);
    } else if (errtoken == OBJECT_INSTANTIATION_INVALID_ARGCOUNT) {
        name = va_arg(argp, char *);
        t1 = va_arg(argp, int);
        t2 = va_arg(argp, int);
        printf("invalid argcount for object instantiation");
        printf("\n\t[class: %s][expected: %d][received: %d]",
               name, t1, t2);
    } else if (errtoken == ARITHMETIC_OP_TYPE_MISMATCH) {
        name = va_arg(argp, char *);
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        t2 = va_arg(argp, int);
        type2 = type_name_from_token(t2);
        printf("conflicting types for arithmetic operation '%s' ", name);
        printf("\n\t[type 1: %s][type 2: %s]", type1, type2);
    } else if (errtoken == COMPARISON_OP_TYPE_MISMATCH) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        t2 = va_arg(argp, int);
        type2 = type_name_from_token(t2);
        printf("conflicting types for comparison operation");
        printf("\n\t[type 1: %s][type 2: %s]", type1, type2);
    } else if (errtoken == UNIMINUS_EXPR_NOT_INT) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        printf("uniminus expression not an integer");
        printf("\n\t[bad type: %s]", type1);
    } else if (errtoken == NOT_EXPR_NOT_BOOL) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        printf("not expr with non-boolean expression");
        printf("\n\t[bad type: %s]", type1);
    } else if (errtoken == COMPARISON_OP_TYPES_NOT_INT) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        t2 = va_arg(argp, int);
        type2 = type_name_from_token(t2);
        printf("one of comparison operand types is not an integer");
        printf("\n\t[type 1: %s][type 2: %s]", type1, type2);
    } else if (errtoken == EXPECTED_INT_OPERANDS) {
        name = va_arg(argp, char *);
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        t2 = va_arg(argp, int);
        type2 = type_name_from_token(t2);
        printf("'%s' operator expects integer operands", name);
        printf("\n\t[type 1: %s][type 2: %s]", type1, type2);
    } else if (errtoken == OUT_STRING_EXPECTS_STRING) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        printf("function out_string expects string argument");
        printf("\n\t[got: %s]", type1);
    }
    printf("\n");
    va_end(argp);
}
