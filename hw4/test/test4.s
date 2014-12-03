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
	.data
	.align 4
	.type _Main_i, @object
	.size _Main_i,4
_Main_i:
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

			# Line 7 - while loop
WH0:
	movl _Main_i, %ebx
	movl $5, %edx
	cmpl %edx, %ebx
	setl %al
	movzbl %al, %eax
	movl %eax, %edx
	testl %edx, %edx
	je WH1
	.data
.LC3:
	.string ">"
	.text
	movl $.LC3, %ebx
			# Line 8 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC2, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
			# Line 9 - scan
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl $_uncool_input, 4(%esp)
	movl $.LC0, (%esp)
	call scanf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _uncool_input, %ecx
			# Line 9 - assignment
	movl %ecx, _Main_y
	.data
.LC4:
	.string ">"
	.text
	movl $.LC4, %ebx
			# Line 10 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC2, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
			# Line 11 - scan
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl $_uncool_input, 4(%esp)
	movl $.LC0, (%esp)
	call scanf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _uncool_input, %ecx
			# Line 11 - assignment
	movl %ecx, _Main_x
	movl _Main_x, %ebx
	movl _Main_y, %edi
	cmpl %edi, %ebx
	setl %al
	movzbl %al, %eax
	movl %eax, %edi
			# Line 12 - if statement
	testl %edi, %edi
	je IF2
	movl _Main_y, %ebx
	jmp IF3
IF2:
	movl _Main_x, %edi
	movl %edi, %ebx
IF3:
			# Line 12 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _Main_i, %ecx
	movl $1, %edi
	addl %ecx, %edi
			# Line 14 - assignment
	movl %edi, _Main_i
	jmp WH0
WH1:

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
