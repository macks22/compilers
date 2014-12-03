// gen.c
//


/**
 * Generate code for the file header.
 */
void * gheader()
{
    printf("\t.section\t.rodata.str1.1,"aMS",@progbits,1\n");
    printf(".data\n");
    printf(".LC0:\n\t.string \"%d\"\n");
    printf(".LC1:\n\t.string \"%d \"\n");
    printf(".LC2:\n\t.string \"%s \"\n");
    printf("\t.align 4\n");
    printf("\t.type _uncool_input,@object\n");
    printf("\t.size _uncool_input,4\n");
    printf("_uncool_input:\n");
    printf("\t.long 0\n");
    printf("\t.text\n");
    printf("\t.globl main\n");
    printf("\t.type\tmain, @function\n");
    gmain_head();
}

/**
 * Generate the setup portion of the main function.
 */
void * gmain_head()
{
    printf("main:\n");
    printf("\tleal\t4(%esp), %ecx\n");
    printf("\tandl\t$-16, %esp\n");
    printf("\tpushl\t-4(%ecx)\n");
    printf("\tpushl\t%ebp\n");
    printf("\tmovl\t%esp, %ebp\n");
    printf("\tpushl\t%ecx\n");
    printf("\tsubl\t$128,%esp\n");
    printf("\tmovl\t%ebx,-16(%ebp)\n");
    printf("\tmovl\t%esi,-20(%ebp)\n");
    printf("\tmovl\t%edi,-24(%ebp)\n");
}

/**
 * Generate code for the file footer.
 */
void * gfooter()
{
    printf("\tmovl\t-16(%ebp),%ebx\n");
    printf("\tmovl\t-20(%ebp),%esi\n");
    printf("\tmovl\t-24(%ebp),%edi\n");
    printf("\taddl\t$128,%esp\n");
    printf("\tpopl\t%ecx\n");
    printf("\tpopl\t%ebp\n");
    printf("\tleal\t-4(%ecx), %esp\n");
    printf("\tret\n");
    printf("\t.size\tmain, .-main\n");
    printf("\t.section\t.note.GNU-stack,"",@progbits\n");
}

/**
 * Generate code to print an int.
 */
void * gprint_int(int val)
{

}

/**
 * Generate code to print a string.
 */
void * gprint_string(char * val)
{

}
