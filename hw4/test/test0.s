	.section	.rodata.str1.1,"aMS",@progbits,1
	.data
.LC0:
	.string "%d"
.LC1:
	.string "%d "
.LC2:
	.string "%s "
	.align 4
	.type _uncool_input,@object
	.size _uncool_input,4
_uncool_input:
	.long 0
	.text
	.globl main
	.type   main, @function
main:
	leal    4(%esp), %ecx
	andl    $-16, %esp
	pushl   -4(%ecx)
	pushl   %ebp
	movl    %esp, %ebp
	pushl    %ecx
	subl  $128,%esp
	movl %ebx,-16(%ebp)
	movl %esi,-20(%ebp)
	movl %edi,-24(%ebp)

	movl $32, %ebx
			# Line 3 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx

	movl -16(%ebp),%ebx
	movl -20(%ebp),%esi
	movl -24(%ebp),%edi
	addl        $128,%esp
	popl    %ecx
	popl    %ebp
	leal    -4(%ecx), %esp
	ret
	.size   main, .-main
	.section        .note.GNU-stack,"",@progbits
