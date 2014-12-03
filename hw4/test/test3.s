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
	.type _Main_y, @object
	.size _Main_y,4
_Main_y:
	.long 0
	.data
	.align 4
	.type _Main_x, @object
	.size _Main_x,4
_Main_x:
	.long 2
	.text
	.globl _Main_print_fn
	.type _Main_print_fn, @function
_Main_print_fn:
	pushl %ebp
	movl %esp, %ebp
	subl $128, %esp
	movl %ebx,-16(%ebp)
	movl %esi,-20(%ebp)
	movl %edi,-24(%ebp)
	movl 8(%ebp), %ebx
	movl $2, %edx
	imull %ebx, %edx
			# Line 5 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %edx, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %edx, %eax

	movl -16(%ebp),%ebx
	movl -20(%ebp),%esi
	movl -24(%ebp),%edi
	addl $128, %esp
	movl %ebp, %esp
	popl %ebp
	ret
	.size _Main_print_fn, .-_Main_print_fn
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

	movl $9, %ebx
			# Line 8 - assignment
	movl %ebx, _Main_y
	movl $4, %edx
	movl _Main_x, %ecx
	imull %edx, %ecx
	movl _Main_y, %edx
	movl $4, %edi
	subl %edi, %edx
	addl %ecx, %edx
	movl %edx, 0(%esp)
			# Line 9 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_print_fn
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %edx
			# Line 9 - assignment
	movl %edx, _Main_x
	movl _Main_x, %ebx
			# Line 10 - print
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
