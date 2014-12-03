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
.LC3:
	.string "abcd"
	.align 4
	.type _Main_s, @object
	.size _Main_s,4
_Main_s:
	.long .LC3
	.data
	.align 4
	.type _Main_x, @object
	.size _Main_x,4
_Main_x:
	.long 0
	.data
	.align 4
	.type _Main_y, @object
	.size _Main_y,4
_Main_y:
	.long 10
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

			# Line 6 - scan
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl $_uncool_input, 4(%esp)
	movl $.LC0, (%esp)
	call scanf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _uncool_input, %ebx
			# Line 6 - assignment
	movl %ebx, _Main_x
	.data
.LC4:
	.string "test"
	.text
	movl $.LC4, %edx
			# Line 7 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %edx, 4(%esp)
	movl $.LC2, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _Main_s, %ebx
			# Line 8 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC2, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _Main_x, %edx
	movl $2, %ecx
	imull %edx, %ecx
	movl _Main_y, %edx
	movl $4, %edi
	subl %edi, %edx
	addl %ecx, %edx
			# Line 9 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %edx, 4(%esp)
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
