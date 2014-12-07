// symstack.h
//
// This module implements a symbol stack, which is meant to be used to hold
// local variables for the compiler. This is not really ideal for type and scope
// checking, but it should be sufficient for generating correct code for
// function calls and generally handling local variables.
//
// This symbol table will need to be able to handle nested function calls. So if
// one function calls another, it must be able to return from the second into
// the first and still have access to its local variables. Therefore we need a
// stack of frames (virtual stack emulator), where each frame contains a number
// of symbols (guaranteed no more than 10 for this assignment).
//
// Thankfully, the symbol table (symtable) already provides everything needed
// for a frame implementation, so we'll just reuse that. We're also just going
// to say that there can be more than 50 nested calls, so we can statically
// define the number of frames in the symstack;
//
// We also want to do some nice abstraction things with the idea of there being
// a base pointer and a stack pointer, such that indexing in the symstack is
// reflective of indexing in the actual stack. Imagine that a function call is
// about to happen. What takes place? The arguments being passed in are loaded
// onto the stack using offsets from the stack pointer, with the leftmost being
// at the offset 0, and the rightmost (nth) being at the offset 4n. So really
// what we want to do is process the arguments from left to right, pushing each
// onto a new stack frame, with each call to push incrementing an internal
// tracker of the next free "offset in the stack". This tracker will start out
// at 0, increment to 4 on the first call, and so on, until capping out at 124
// (4 * 31). Hence there are 32 symbols which can be in the stack.
//
// However, the other thing we want to be able to do with this structure is deal
// with local variables that are not passed in as arguments to a method. These
// are declared on the go, in the middle of a scope. Normally these might be
// allocated using negative offsets from the base point (%ebp).
//
// INSIGHT!
//
// We can simplifiy this whole process by making a few observations:
// (1) let calls are the same as immediately executed anonymous functions. They
//     take an argument list, execute one or more expressions, and return a
//     value. Inside the let, the only local variables are those passed in.
// (2) When YACC processes a method declaration, and a let declaration, there
//     can be no inner method declarations, and any inner let declarations will
//     be processed in their entirety before the outer one is actually
//     processed. Hence generating... MAYBE NOT! Seems things are evaluated left
//     to right after all... moving on for now.

#include "lib/symtable.h"

// guaranteed no more than 10 for this assignment, but let's just be safe
#define NUM_SYMBOLS 32

#define NUM_FRAMES 50

typedef Symtable Frame;

typedef struct {
    Frame *frames[NUM_FRAMES]; // the actual frames
    int curframe;              // maintain index of currently active frame.
    int cur_offset;            // track the next free offset, incrementing by 4
} Symstack;

Symstack * ss_create();
void * ss_destroy(Symstack *ss);

void * ss_push_frame(Symstack *ss);
void * ss_pop_frame(Symstack *ss);

int * ss_put_attr(Symstack *ss, char *name);
