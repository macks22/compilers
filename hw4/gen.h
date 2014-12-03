// gen.h
//
// Code generation functions and data structures.

static int curlabel;  // track the most recently assigned label

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
 * Generate code to print an int.
 */
void * gprint_int(int val);

/**
 * Generate code to print a string.
 */
void * gprint_string(char * val);
