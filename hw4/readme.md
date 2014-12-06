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

# Running Notes

This section is used for a running implementation brainstorm.

## Arithmetic Expressions

There are only 3 arithmetic expressions: '+', '-', '*'. For each of these, we
simply take the registers of the operands and put them into an appropriate
assembly expression:

'+': addl
'-': subl
'*': imull

## Procedure Calls

Procedure calls are invoked with the following convention:

*   Arguments are pushed onto the stack from right to left
*   Caller saves caller-save registers
*   `call <func>` is used to jump to the function label
*   Callee saves callee-save registers
*   function executes
*   Callee restores callee-save registers
*   `ret` is used to return to wherever `call` left off
*   Caller restores caller-save registers

So before the call, args are pushed on like so:

*   pushl <argn> 
*   ...
*   pushl <arg1>

Which, with our statically allocated 128 stack bytes, corresponds to:

*   movl <val>, 4n(%esp)
*   ...
*   movl <val>,  0(%esp)

When the procedure actually has arguments, the callee can access them using
offsets from the frame pointer, as follows:

*    0(%ebp) = old %ebp
*    4(%ebp) = return address
*    8(%ebp) = 1st arg
*   12(%ebp) = 2nd arg
*   16(%ebp) = 3rd arg
*   ...

So when placing variables onto the stack at %esp offsets, we can simply store
the eventual offset locations from %ebp. To calculate the eventual offsets,
simply add 4 to the %esp offset.

These references are essentially pulling things from the callers stack frame by
using positive offsets from the bottom of its own frame (negative offsets move
down into the callee frame). Note that `call` pushes the return address on the
stack, and the first thing any function does is push the old frame pointer onto
the stack, leaving it at position 0(%ebp).

This portion of the assembly generation could all be managed with something like
a virtual stack, which emulates the assembly stack, writing out the operations
to be performed instead of actually performing them.

Alternatively:
Inside the function, these should be given these offsets as labels or all args
should be immediately loaded into registers.

*   `actual_list` is the only place where arguments are passed into method calls
*   `formal_list` is used for method and let declaration. Therefore id
    declarations in the RHS of `formal` are the only ones which will use esp
    offsets

## Variables

Variables are one of the more interesting pieces of the puzzle. Here we have two
types of varaibles: global and local, with global being the simpler case.

**Globals**

For global variables, we need to define top-level labels to be used to hold the
variable values. These do not need to be stored in the stack. A variable x would
be defined as follows.

	.data
	.align 4
	.type _Main_x, @object
	.size _Main_x,4
_Main_x:
	.long 0

Notes:

*   The header portion is the same for all variables
*   The value after the .long tag is the initial value of the variable
*   The initial value for an integer is the number declared
*   If no number is declared, the initial value for an integer is 0
*   Strings are always defined and declared at the same time
*   The initial value for strings should be the label of the string

**Locals**

Local variables are much more challenging than global variables, since they are
stored in the stack dynamically.

### Lookup

### Declaration

## Control Flow

### IF

x in %edx, y in %ecx
z <- if (x < y) then y else x fi

    cmpl    %ecx, %edx  # execute %edx - %ecx : set CCs
    setl    %al         # set if less; if SB is negative
    movzbl  %al, %eax   # move zero extended (1 if x < y, else 0)
    cmpl    $0, %eax    # put into EAX: 0 if true, else something non-zero
    je      .L2         # if !(x < y), jump to .L2
    # then y
    movl %ecx, _Main_z  # z <- y
    jmp .L3            # skip the else clause
.L2:
    # else x
    movl %edx, _Main_z  # z <- x
.L3:
    ...

### WHILE

i in %edx, y in %ecx
while i <= y loop ...body... pool

.L0
    cmpl    %ecx, %edx  # execute %edx - %ecx : set CCs (i - y)
    setle   %al
    movzbl  %al, %eax
    cmpl    $0, %eax
    je      .L1
    ...body...
    jmp     .L0
.L1
    ...

Need 2 labels, 2 jumps, and one comparison.
