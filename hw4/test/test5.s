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
	.long 0
	.text
	.globl _Main_factorial
	.type _Main_factorial, @function
_Main_factorial:
	pushl %ebp
	movl %esp, %ebp
	subl $128, %esp
	movl %ebx,-16(%ebp)
	movl %esi,-20(%ebp)
	movl %edi,-24(%ebp)
	movl 8(%ebp), %ebx
	movl $2, %edx
	cmpl %edx, %ebx
	setl %al
	movzbl %al, %eax
	movl %eax, %edx
			# Line 5 - if statement
	testl %edx, %edx
	je IF0
	movl $1, %ebx
	jmp IF1
IF0:
	movl 8(%ebp), %edx
	movl $1, %ecx
	subl %ecx, %edx
	movl %edx, 0(%esp)
			# Line 5 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_factorial
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %edx
	movl 8(%ebp), %ecx
	movl $2, %edi
	subl %edi, %ecx
	movl %ecx, 0(%esp)
			# Line 5 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_factorial
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %ecx
	addl %edx, %ecx
	movl %ecx, %ebx
IF1:
	movl %ebx, %eax

	movl -16(%ebp),%ebx
	movl -20(%ebp),%esi
	movl -24(%ebp),%edi
	addl $128, %esp
	movl %ebp, %esp
	popl %ebp
	ret
	.size _Main_factorial, .-_Main_factorial
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

			# Line 9 - scan
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl $_uncool_input, 4(%esp)
	movl $.LC0, (%esp)
	call scanf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _uncool_input, %ebx
			# Line 9 - assignment
	movl %ebx, _Main_y
	movl _Main_y, %edx
	movl %edx, 0(%esp)
			# Line 10 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_factorial
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %edx
			# Line 10 - assignment
	movl %edx, _Main_x
	movl _Main_x, %ebx
			# Line 11 - print
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
