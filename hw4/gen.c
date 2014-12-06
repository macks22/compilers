// gen.c
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
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

char *
gfunc_name(char *func_name, char *class_name)
{
    char *fname = calloc(128, sizeof(char));
    if (strcmp(func_name, "main") == 0) {
        strcpy(fname, "main");
    } else {
        sprintf(fname, "_%s_%s", class_name, func_name);
    }
    return fname;
}

/**
 * Generate the setup portion of a function.
 */
void * gfunc_head(char *func_name, char *class_name)
{
    char *fname = gfunc_name(func_name, class_name);
    printf("#%s:\n", fname);

    printf("\t.text\n");
    printf("\t.globl\t%s\n", fname);
    printf("\t.type\t%s, @function\n", fname);
    printf("%s:\n", fname);
    printf("\tpushl\t%%ebp\n"
           "\tmovl\t%%esp,%%ebp\n"
           "\tsubl\t$128,%%esp\n");  // allocate 128 bytes on the stack

    gcallee_save();
    free(fname);
}

/**
 * Generate teardown portion of a function.
 */
void * gfunc_foot(char *func_name, char *class_name)
{
    char *fname = gfunc_name(func_name, class_name);
    gcallee_restore();
	printf("\taddl $128,%%esp\n"
	       "\tmovl\t%%ebp,%%esp\n"
	       "\tpopl\t%%ebp\n"
	       "\tret\n");
	printf("\t.size %s, .-%s\n", fname, fname);
    free(fname);
}

/**
 * Generate code for the main function.
 */
void * gmain_head()
{
    printf("#main:\n");
    printf("\t.text\n");
    printf("\t.globl\tmain\n"
           "\t.type\tmain, @function\n"
           "main:\n"
           "\tleal\t4(%%esp),%%ecx\n"
           "\tandl\t$-16,%%esp\n"
           "\tpushl\t-4(%%ecx)\n"
           "\tpushl\t%%ebp\n"
           "\tmovl\t%%esp,%%ebp\n"
           "\tpushl\t%%ecx\n"
           "\tsubl\t$128,%%esp\n");
    gcallee_save();
}

/**
 * Generate strings for format args to i/o functions.
 */
void * gio_labels()
{
    printf("#LABELS:\n");
    printf("\t.data\n"
           ".fmt_int:\n\t.string \"%%d\\n\"\n"
           ".fmt_str:\n\t.string \"%%s\\n\"\n"
           ".fmt_int_input:\n\t.string \"%%d\"\n"
           "\t.align 4\n"
           "\t.type\t_uncool_input,@object\n"
           "\t.size\t_uncool_input,4\n"
           "_uncool_input:\n"
           "\t.long 0\n");
    printf("#END LABELS\n");
}

/**
 * Generate code for the file header.
 */
void * gheader()
{
    curlabel = 0;
    printf("#HEADER:\n");
    printf("\t.section\t.rodata.str1.1,\"aMS\",@progbits,1\n");
    gio_labels();
    printf("#END HEADER\n");
}

/**
 * Generate code for the file footer.
 */
void * gfooter()
{
    printf("\n#FOOTER:\n");
    printf("\taddl\t$128,%%esp\n"
           "\tpopl\t%%ecx\n"
           "\tpopl\t%%ebp\n"
           "\tleal\t-4(%%ecx),%%esp\n"
           "\tret\n"
           "\t.size\tmain, .-main\n"
           "\t.section\t.note.GNU-stack,\"\",@progbits\n");
}

/**
 * Save the callee-save registers just after a function call.
 */
void * gcallee_save()
{
    printf("\t#CALLEE SAVE\n");
    printf("\tmovl\t%%ebx,-16(%%ebp)\n"
           "\tmovl\t%%esi,-20(%%ebp)\n"
           "\tmovl\t%%edi,-24(%%ebp)\n"
           "\n");
}

/**
 * Restore the callee-save registers just before returning.
 */
void * gcallee_restore()
{
    printf("\t#CALLEE RESTORE\n");
    printf("\tmovl\t-16(%%ebp),%%ebx\n"
           "\tmovl\t-20(%%ebp),%%esi\n"
           "\tmovl\t-24(%%ebp),%%edi\n"
           "\n");
}

/**
 * Save caller-save registers just before a function call.
 */
void * gcaller_save()
{
    printf("\t#CALLER SAVE\n");
	printf("\tmovl\t%%edx,-12(%%ebp)\n"
	       "\tmovl\t%%ecx,-8(%%ebp)\n");
}

/**
 * Restore caller-save registers just after returning.
 */
void * gcaller_restore()
{
    printf("\t#CALLER RESTORE\n");
	printf("\tmovl\t-12(%%ebp),%%edx\n"
	       "\tmovl\t-8(%%ebp),%%ecx\n");
}

/**
 * Generate code to print an int.
 * :param reg: contains the integer to print.
 */
char *
gprint_int(char * reg)
{
    gcaller_save();
    printf("\t#CALL PRINTF (OUT_INT)\n");
    printf("\tmovl\t%s,4(%%esp)\n", reg);
    printf("\tmovl\t$.fmt_int,(%%esp)\n"
           "\tcall\tprintf\n");
    gcaller_restore();
    return reg;
}

/**
 * Generate code to print a string.
 */
char *
gprint_string(char * reg)
{
    gcaller_save();
    printf("\t#CALL PRINTF (OUT_STRING)\n");
    printf("\tmovl\t%s,4(%%esp)\n", reg);
    printf("\tmovl\t$.fmt_str,(%%esp)\n"
           "\tcall\tprintf\n");
    gcaller_restore();
    return reg;
}

/**
 * Declare a new string wherever we happen to be in the assembly code.
 */
char *
gstring_label(char * str)
{
    char *label = get_label();
    printf("\t.data\n"
           "%s:\n", label);
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
void * gload_string(char *label, char *reg)
{
    printf("\tmovl\t$%s,%s\n", label, reg);
}

/**
 * Load a global variable reference into the given register.
 */
void * gload_var_ref(char *label, char *reg)
{
    printf("\tmovl\t%s,%s\n", label, reg);
}

/**
 * Gen code to load a value from a stack offset into register `reg`.
 */
void * gload_stack_ref(int offset, char *reg)
{
    printf("\tmovl\t%s,%s\n", gstack_ref(offset), reg);
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

/**
 * Gen code to get input from user.
 * The register passed in ends up with the input value.
 */
void *
ginput(char *reg)
{
    gcaller_save();
    printf("\t#CALL SCANF\n");
    printf("\tmovl\t$_uncool_input,4(%%esp)\n"
           "\tmovl\t$.fmt_int_input,(%%esp)\n"
           "\tcall\tscanf\n");
    gcaller_restore();
    printf("\tmovl\t_uncool_input,%s\n", reg);
}

/**
 * Gen code to declare a global integer.
 */
char *
gdecl_globl_int(char *varname, int val)
{
    char *as_name = calloc(128, sizeof(char));
    sprintf(as_name, "_Main_%s",  varname);

    printf("#%s:\n", as_name);
    printf("\t.data\n"
           "\t.align 4\n"
	       "\t.type %s, @object\n", as_name);
	printf("\t.size %s, 4\n", as_name);
    printf("%s:\n", as_name);
    printf("\t.long %d\n", val);
    return as_name;
}

/**
 * Gen code to declare a global string
 * :param varname: The name of the variable to declare.
 * :param label: The label previously written for this string.
 */
char *
gdecl_globl_string(char *varname, char *label)
{
    char *as_name = calloc(128, sizeof(char));
    sprintf(as_name, "_Main_%s",  varname);

    printf("#%s:\n", as_name);
    printf("\t.data\n"
           "\t.align 4\n"
           "\t.type %s, @object\n", as_name);
    printf("\t.size %s, 4\n", as_name);
    printf("%s:\n", as_name);
    printf("\t.long %s\n", label);
    return as_name;
}

/**
 * Gen code to add two values (from registers).
 */
char *
gadd(char *src, char *dest)
{
    printf("\taddl\t%s,%s\n", src, dest);
    return dest;
}

/**
 * Gen code to subtract two values (from registers).
 * Note that the first register passed will be unused afterwards.
 */
char *
gsub(char *src, char *dest)
{
    // dest = dest - src
    printf("\tsubl\t%s,%s\n", src, dest);
    return dest;
}

/**
 * Gen code to multiply two values (from registers).
 */
char *
gimul(char *src, char *dest)
{
    printf("\timull\t%s,%s\n", src, dest);
    return dest;
}

/**
 * Get a stack reference at the given offset.
 * This will be an offset down from the frame pointer %ebp.
 */
char * gstack_ref(int offset)
{
    char *ref = calloc(128, sizeof(char));
    sprintf(ref, "-%d(%%ebp)", offset);
    return ref;
}

/**
 * Gen code for basic move op.
 */
void * gmov(char *src, char *dest)
{
    printf("\tmovl\t%s,%s\n", src, dest);
}

/**
 * Gen code to update the attribute. If global, the assignment will
 * be made to the global label. Otherwise, the stack reference will
 * be used for the assignment.
 */
void *
gassign(Symbol *attr, char *reg)
{
    assert(attr != NULL);
    if (is_global(attr)) {
        gmov(reg, attr->label);
    } else {  // local
        gmov(reg, gstack_ref(attr->offset));
    }
}

/**
 * Gen code to call the class method.
 */
void * gcall(char *func_name, char *class_name)
{
    char *fname = gfunc_name(func_name, class_name);
    gcaller_save();
    printf("\tcall\t%s\n", fname);
    gcaller_restore();
}

/**
 * Gen string label which represents an offset from a register.
 */
char *
greg_offset(char *reg, int offset)
{
    char *label = calloc(128, sizeof(char));
    sprintf(label, "%d(%%%s)", offset, reg);
    return label;
}

/**
 * Put an argument onto the stack at an esp offset before making a call.
 */
void * gcaller_pass(char *reg, char *esp_loc)
{
    printf("\tmovl\t%s,%s\n", reg, esp_loc);
}
