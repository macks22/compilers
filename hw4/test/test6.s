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
	.data
	.align 4
	.type _Main_x, @object
	.size _Main_x,4
_Main_x:
	.long 7
	.text
	.globl _Main_f
	.type _Main_f, @function
_Main_f:
	pushl %ebp
	movl %esp, %ebp
	subl $128, %esp
	movl %ebx,-16(%ebp)
	movl %esi,-20(%ebp)
	movl %edi,-24(%ebp)
	movl 8(%ebp), %ebx
			# Line 6 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
			# Line 7 - start let
	movl $8, %edx
			# Line 8 - assignment
	movl %edx, -32(%ebp)
	movl $1, %ecx
			# Line 8 - assignment
	movl %ecx, -36(%ebp)
	movl -32(%ebp), %edx
	movl -36(%ebp), %edi
	addl %edx, %edi
			# Line 9 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %edi, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
			# Line 11 - end let
	movl 8(%ebp), %ebx
			# Line 12 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %ebx, %eax

	movl -16(%ebp),%ebx
	movl -20(%ebp),%esi
	movl -24(%ebp),%edi
	addl $128, %esp
	movl %ebp, %esp
	popl %ebp
	ret
	.size _Main_f, .-_Main_f
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

	movl _Main_x, %ebx
			# Line 17 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
			# Line 18 - start let
	movl $2, %edx
			# Line 19 - assignment
	movl %edx, -32(%ebp)
	movl $3, %ecx
			# Line 19 - assignment
	movl %ecx, -36(%ebp)
	movl -32(%ebp), %edx
	movl %edx, 0(%esp)
			# Line 20 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_f
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %edx
	movl -32(%ebp), %ecx
	movl -36(%ebp), %edi
	addl %ecx, %edi
			# Line 21 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %edi, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
			# Line 23 - end let
	movl _Main_x, %ebx
			# Line 24 - print
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
