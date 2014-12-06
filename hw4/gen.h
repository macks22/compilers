// gen.h
//
// Code generation functions and data structures.

#include "lib/symtable.h"

extern int curlabel;  // track the most recently assigned label
extern int curlabel_if;

/**
 * Get a new unique label. These labels take the from L<x>, where
 * x is a positive integer; x is 0 for the first label and gets
 * incremented at each call.
 */
char * get_label();

/**
 * Get next IF statement label.
 */
char * get_label_if();

/**
 * Generate code for the file header.
 */
void * gheader();

/**
 * Generate code for the file footer.
 */
void * gfooter();

/**
 * Generate the setup portion of a function.
 */
void * gfunc_head(char *func_name, char *class_name);

/**
 * Generate teardown portion of a function.
 */
void * gfunc_foot(char *func_name, char *class_name);

/**
 * Generate code for the main function.
 */
void * gmain_head();

/**
 * Gen code to end function (callee-save + anything else).
 */
void * gfunc_foot();

/**
 * Generate code to print an int from a register.
 */
char * gprint_int(char * reg);

/**
 * Generate code to print a string from a register.
 */
char * gprint_string(char * reg);

/**
 * Generate code to save the callee-save registers just after a function call.
 */
void * gcallee_save();

/**
 * Generate code to restore the callee-save registers just before returning.
 */
void * gcallee_restore();

/**
 * Save caller-save registers just before a function call.
 */
void * gcaller_save();

/**
 * Restore caller-save registers just after returning.
 */
void * gcaller_restore();

/**
 * Declare a new string wherever we happen to be in the assembly code.
 */
char * gstring_label(char * str);

/**
 * Gen code to load the integer val into the given register `reg`.
 */
void * gload_int(int val, char *reg);

/**
 * Gen code to load the string `val` into the given register `reg`.
 */
void * gload_string(char *label, char *reg);

/**
 * Load a global variable reference into the given register.
 */
void * gload_var_ref(char *label, char *reg);

/**
 * Gen code to load a value from a stack offset into register `reg`.
 */
void * gload_stack_ref(int offset, char *reg);

/**
 * Generate code to return an integer value to a calling function.
 */
char * greturn_int(int val);

/**
 * Gen code to return the value in a particular register from a function.
 */
char * greturn(char *reg);

/**
 * Gen code to get input from user.
 */
void * ginput();

/**
 * Gen code to declare a global integer.
 */
char * gdecl_globl_int(char *varname, int val);

/**
 * Gen code to declare a global string
 * :param varname: The name of the variable to declare.
 * :param label: The label previously written for this string.
 */
char * gdecl_globl_string(char *varname, char *val);

/**
 * Gen code to add two values (from registers).
 */
char * gadd(char *src, char *dest);

/**
 * Gen code to subtract two values (from registers).
 */
char * gsub(char *src, char *dest);

/**
 * Gen code to multiply two values (from registers).
 */
char * gimul(char *src, char *dest);

/**
 * Gen code to get logical not of value in register.
 * The result is stored back in the same register.
 */
char * gnot(char *dest);

/**
 * Gen code to get negation of an integer value stored in the dest register.
 */
char * gneg(char *dest);

/**
 * Get a stack reference at the given offset.
 * This will be an offset down from the frame pointer %ebp.
 */
char * gstack_ref(int offset);

/**
 * Gen code for basic move op.
 */
void * gmov(char *src, char *dest);

/**
 * Gen code to update the attribute. If global, the assignment will
 * be made to the global label. Otherwise, the stack reference will
 * be used for the assignment.
 */
void * gassign(Symbol *attr, char *reg);

/**
 * Gen string label which represents an offset from a register.
 */
char * greg_offset(char *reg, int offset);

/**
 * Put an argument onto the stack at an esp offset before making a call.
 */
void * gcaller_pass(char *reg, char *esp_loc);

/**
 * Gen code to call the class method.
 */
char * gcall(char *func_name, char *class_name);

/**
 * Gen code to compare two registers.
 * The result will be stored in %eax and %eax will be returned,
 * so it can be used for conditional jump calls.
 * For x < y, x will be first and y will be second.
 */
char * gcmp(int comparator, char *first, char *second);

/**
 * Gen code to jump to label using given jump op.
 */
void * gjump(char *label, char *jump_op);

/**
 * Generate the given label at the current position.
 */
void * glabel(char *label);
