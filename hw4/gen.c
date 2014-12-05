// gen.c
//

#include <stdlib.h>
#include <stdio.h>
#include "gen.h"
#include "registers.h"

int curlabel;

/**
 * Get a new unique label. These labels take the from L<x>, where
 * x is a positive integer; x is 0 for the first label and gets
 * incremented at each call. Labels up to 999 allowed.
 */
char * get_label()
{
    char * buf = calloc(7, sizeof(char));  // labels up to 999 allowed
    sprintf(buf, ".LC%d", curlabel++);
    return buf;
}

/**
 * Generate the setup portion of the main function.
 */
void * gmain_head()
{
    printf("main:\n");
    printf("\tleal\t4(%%esp),%%ecx\n");
    printf("\tandl\t$-16,%%esp\n");
    printf("\tpushl\t-4(%%ecx)\n");
    printf("\tpushl\t%%ebp\n");
    printf("\tmovl\t%%esp,%%ebp\n");
    printf("\tpushl\t%%ecx\n");
    printf("\tsubl\t$128,%%esp\n");
}

/**
 * Generate code for the file header.
 */
void * gheader()
{
    curlabel = 2;
    printf("\t.section\t.rodata.str1.1,\"aMS\",@progbits,1\n");
    printf("\t.data\n");
    printf(".LC0:\n\t.string \"%%d\\n\"\n");
    printf(".LC1:\n\t.string \"%%s\\n\"\n");
    printf("\t.align 4\n");
    printf("\t.type\t_uncool_input,@object\n");
    printf("\t.size\t_uncool_input,4\n");
    printf("_uncool_input:\n");
    printf("\t.long 0\n");
    printf("\t.text\n");
    printf("\t.globl\tmain\n");
    printf("\t.type\tmain, @function\n");
    gmain_head();
}

/**
 * Generate code for the file footer.
 */
void * gfooter()
{
    printf("\taddl\t$128,%%esp\n");
    printf("\tpopl\t%%ecx\n");
    printf("\tpopl\t%%ebp\n");
    printf("\tleal\t-4(%%ecx),%%esp\n");
    printf("\tret\n");
    printf("\t.size\tmain, .-main\n");
    printf("\t.section\t.note.GNU-stack,\"\",@progbits\n");
}

/**
 * Save the callee-save registers just after a function call.
 */
void * gcallee_save()
{
    printf("\tmovl\t%%ebx,-16(%%ebp)\n");
    printf("\tmovl\t%%esi,-20(%%ebp)\n");
    printf("\tmovl\t%%edi,-24(%%ebp)\n");
}

/**
 * Restore the callee-save registers just before returning.
 */
void * gcallee_restore()
{
    printf("\tmovl\t-16(%%ebp),%%ebx\n");
    printf("\tmovl\t-20(%%ebp),%%esi\n");
    printf("\tmovl\t-24(%%ebp),%%edi\n");
}

/**
 * Generate code to print an int.
 * :param reg: contains the integer to print.
 */
char *
gprint_int(char * reg)
{
    char *return_reg;
    gcallee_save();  // TODO: may drop the value to be printed
    printf("\tmovl\t%s,4(%%esp)\n", reg);
    printf("\tmovl\t$.LC0,(%%esp)\n");
    printf("\tcall printf\n");
    return_reg = greturn_int(0);
    gcallee_restore();
    return return_reg;
}

/**
 * Generate code to print a string.
 */
char *
gprint_string(char * reg)
{
    char *return_reg;
    gcallee_save();  // TODO: may drop the value to be printed
    printf("\tmovl\t%s,4(%%esp)\n", reg);
    printf("\tmovl\t$.LC1,(%%esp)\n");
    printf("\tcall printf\n");
    return_reg = greturn_int(0);
    gcallee_restore();
    return return_reg;
}

/**
 * Declare a new string wherever we happen to be in the assembly code.
 */
char *
gstring_label(char * str)
{
    char *label = get_label();
    printf("\t.data\n");
    printf("%s:\n", label);
    printf("\t.string \"%s\"\n", str);
    printf("\t.text\n");
    return label;
}

/**
 * Gen code to load the integer val into the given register `reg`.
 */
void * gload_int(int val, char *reg)
{
    printf("\tmovl\t$%d,%s\n", val, reg);
}

/**
 * Gen code to load the string `val` into the given register `reg`.
 */
void * gload_string(char *val, char *reg)
{
    char *label = gstring_label(val);
    printf("\tmovl\t$%s,%s\n", label, reg);
}

/**
 * Generate code to return an integer value to a calling function.
 */
char *
greturn_int(int val)
{
    printf("\tmovl\t$%d,%%eax\n", val);
    return "%eax";
}
