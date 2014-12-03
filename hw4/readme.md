% Mack Sweeney
% CS540 UnCool Compiler Design Doc

# Overview

This is the design doc for an UnCool to IA32 compiler. This compiler will use a
very naive code generation approach, with simple mappings from UnCool language
constructs to chunks of IA32 code necessary to execute them. The goal is to
generate code that is correct and to minimize the complexity of generation. In
other words, the IA32 code generated will be inefficient, repetetive, and
generally quite ugly, but it will work as it's supposed to.

This document lays out the necessary data structures, defines a mid-level API
which will encapsulate core functionality, including symbol table construction
and usage. Using this mid-level API, a high-level API will be defined to be used
in code generation.

# Data Structures

The symbol table from the previous homework will be leveraged to track class,
method, and attribute declarations. YACC will be used to track register
assignments by leveraging syntax-directed translation. The new data structures
will include a RegisterTracker, which will keep track of available registers and
allocate/free them.

# Functions

The following functions define a mid-level interface API to be used by code
generation functions.

// Register handling
char * get_register();
void * free_register(char * register);

// Symbols: Declarations
int declare_attribute(char * attr);
int declare_method(char * method);
int end_method_declaration();
int declare_class(char * class_name);
int end_class_declaration();
int enter_let_scope();
int exit_let_scope();

// Symbols: Lookup & manipulation
char * lookup_attribute(char * attr);
int update_attribute(char * attr, char * val);

## Code Generation

The actual code generation will occur line-by-line, using the information from
the symbol table and the register information attached to non-terminals. For
instance, when a method definition is encountered, a new label will be made for
that method's code, with the standard stack prep before and after.

Boilerplate code will need to be generated for each program, with labels for all
strings, and standard headers and footers for each .s file.

Below is a the high-level API that will be used during code generation. Note
that all functions here are prefaced with a 'g' to indicate they generate code.

// boilerplate
void * gheader();
void * gfooter();
void * gprint_int(int val);
void * gprint_string(char * val);
