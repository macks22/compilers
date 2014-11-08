# Design

This project requires us to implement type checking for the UnCool langauge.
This portion of the README is dedicated to planning and discussion of program
design. Requirements are extracted from the problem description and the overall
flow of program execution is laid out and discussed. Following this discussion,
necessary algorithms and data structures are outlined.

## Requirements

1.  Implement a parser for the UnCool language.
    1.  Most of this code is given in the uncool.l and uncool.y files. It will
        be necessary to verify these work as expected and fully cover the
        specification for the UnCool language.
2.  Implement declaration checking on top of the basic parser.
    1.  Track scope in some data structure(s).
    2.  Verify that all variables referenced are within proper scope.
    3.  Print out error message with VAR NAME & LINE NO for each error.
    4.  Continue processing until EOF even when errors are encountered.
3.  Detect duplicate identifier declarations.
    1.  For methods, features, and class names.
    1.  Print out appropriate error message for each and continue parsing.
4.  Ensure Main class with main() method is present.
5.  Implement type checking on top of the basic parser.
    1.  Operators for all operands must be checked, according to spec below.

        Operation       Operand1        Operand2        Result Type
        ------------    -----------     -----------     ----------------
        +,-,*           Int             Int             Int
        <,<=,>,>=       Int             Int             Bool
        <>,=            Any             Matches op1     Bool
        isVoid          Any             ---             Int
        ~ (uniminus)    Int             ---             Int
        Not             Bool            ---             Bool
        <-              Any             Matches op1     Matches operands

    2.  All statements must be type checked, according to rules below.
        1.  if: Boolean predicate, types of 2 branches (then/else) must match
        2.  while: Boolean predicate, type of statement is type of associated
            expression
        3.  let: creates new scope with types; returns type of expression in
            body.
        4.  sequence of expressions: returns type of last expression in body.
    3.  Arrays can only be dereferenced with integer indices.
    4.  Method definition: type of method must match type of last expression in
        sequence.
    5.  Method calls:
        1.  correct number of arguments passed
        2.  returns type defined in definition (recursive calls can be assumed
            to be correct)

## Overall Program Flow

This program is designed to accept .uc (UnCool) code files. These files are
first fed through the lexer, which matches lexemes from the source file with
tokens defined in the parser. The parser is then fed these tokens from the
lexer, where it matches each to a rule and executes the appropriate actions. It
is here in the parser where additional code needs to be added in order to
perform type/scope/etc checking on the source code.

### Scope Checking

In order to check the scope of variable references, each variable must be placed
within an appropriately scoped symbol table when it is declared. This will also
allow checking of duplicate declaration types and is crucial for determining the
correct type in order to perform type checking. There are 3 types of entities
which can be declared: classes, methods, and attributes. The following rules
govern the scoping of these declarations in UnCool:

1.  all class names are globally visible
2.  all attributes have scope local to class
3.  all methods have global scope, though they are specific to their classes
    -   can be referenced in one of 2 ways:
        1.  <obj>.<method>(params): this is used at the global scope or in the
            class scope, in which case <obj> is "self".
        2.  <id>(params): this is shorthand for self.<method> and can only be
            used in the class scope.
    -   in both cases, the class scope is used to find the appropriate method to
        call

### Type Checking

Type checking will occur after scope checking on a line-by-line basis. In order
to check types, the following information must be available:

1.  operands: type declarations used for each operand
2.  method: scope of class which defines type of object referenced
3.  identifier: type of identifier used during declaration

## Data Structures

1.  Scoping
    -   a scope will be represented by a symbol table
        +   a symbol table will basically be a hash table
        +   a symbol is a string identifier; these serve as hash table keys
        +   the values indexed by symbols are structs
        +   each struct contains the token, type, and value
    -   the global scope will be represented by the symbol table on the bottom
        of the stack
    -   other levels of scope will be represented by subsequent symbol tables on
        the stack.
        +   the top-most scope will be the local scope
2.  Type Checking
    -   type checking is relatively straightforward given the above data
        structures
        +   for a class, simply check the global symbol table for the class
            reference
        +   for a method, find the related class in the global symbol table,
            then look up the method in the class scope to find the type
        +   for any other identifier, first check the local symbol table (top of
            stack) for the symbol, then recurse down the stack.

Will also want to store scope type: global, class, or let

So in summary, we have the following data structures:

1.  arraylist - foundation for stack and hash table
2.  stack - used for hierarchical scope representation
3.  hashtable - foundation for symbol table, built on arraylist
4.  symtable - the symbol table used to represent scope

Initial approach:
-----------------

Since the arraylist will be used for multiple purposes, it will be built as a
generic data structure using void pointers. The hash table will also hold a
variety of types, so void pointers will be used to make it generic. The symtable
will be a wrapper on top of the hash table. It will deal with three different
types of symbol data: class, method, and attribute, where each of these will be
represented with a struct. Either struct inheritance or generic void pointers
may be leveraged here. Struct inheritance imposes slightly more structure, so
that will be used. The stack will simply be a thin wrapper around the arraylist,
with push and pop methods, as well as some way to inspect subsequent layers of
the stack.


After further consideration:
----------------------------

It may be useful just to build the stack and hash table from the ground up
separately, since the arraylist would be used in very different ways --
essentially requiring completely different methods.

## Algorithms

Lexical units in UnCool are:

1.  Integers: non-empty strings of digits 0-9
    -   only used as constants in expressions
2.  Declarations: 3 types
    1.  class
        -   PATTERN: starts with capital letter, prefaced by "class" keyword
        -   ACTION: create new scope to store class methods/attributes; store
            the scope in the global symbol table
    2.  method
        -   PATTERN: starts with lowercase letter, followed by parens ":" TYPE
        -   ACTION: store new method in symbol table for current class scope.
            +   If current scope is not a class scope, raise an error.
            +   Store type and # args for each method declaration.
    3.  attribute
        -   PATTERN: starts with lowercase letter, followed by ":" TYPE
        -   ACTION: store in current scope
3.  References: 3 types
    1.  class, search global symbol table for class scope
        -   if not found, raise error
    2.  method, 2 options
        1.  if object name prefaces method name:
            1.  look up object type in scope stack
            2.  then look up class name in global scope
                -   if not found, raise error
            3.  else look up method name in class scope
                -   if not found, raise error
                -   if argument count doesn't match, raise error
        2.  if no object name prefaces method name:
            1.  check if current scope is class scope
                -   if not, raise error
            2.  look up method name in current scope (proceed as in #3 above)
    3.  attribute, search current scope for identifier
        -   if not found, raise error
        -   otherwise, get type
4.  Special notation:
    1.  '()': after method identifiers to call method
    2.  '[]': after array identifiers to index array
    3.  '{}': after class/method declaration or randomly inside one of these
    4.  ':':  in let statements to separate declarations (possibly elsewhere?)
    5.  ';':  as terminals for expressions and lists of feature
    6.  ':':  after id in declaration to preface type
    7.  '<-': assignment operator
    8.  ',':  between feature declarations in method declaration or let stmt
5.  Operators: used in expressions
    -   binary
        +   arithmetic: (+,-,\*)
        +   comparison: (<, <=, >, >=, <>, =)
    -   unary (~, isvoid)
6.  Conditional: (if <expr> then <expr> else <expr> fi)
7.  Loop: (while <expr> loop <expr> pool)
8.  let statement
9.  new statement
