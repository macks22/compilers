// gen.h
//
// Code generation functions and data structures.

extern int curlabel;  // track the most recently assigned label

/**
 * Get a new unique label. These labels take the from L<x>, where
 * x is a positive integer; x is 0 for the first label and gets
 * incremented at each call.
 */
char * get_label();

/**
 * Generate code for the file header.
 */
void * gheader();

/**
 * Generate code for the file footer.
 */
void * gfooter();

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
void * gload_string(char *val, char *reg);

/**
 * Generate code to return an integer value to a calling function.
 */
char * greturn_int(int val);
