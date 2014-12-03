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
	.long 0
	.data
	.align 4
	.type _Main_size, @object
	.size _Main_size,4
_Main_size:
	.long 0
	.text
	.globl _Main_get_input
	.type _Main_get_input, @function
_Main_get_input:
	pushl %ebp
	movl %esp, %ebp
	subl $128, %esp
	movl %ebx,-16(%ebp)
	movl %esi,-20(%ebp)
	movl %edi,-24(%ebp)
			# Line 5 - start let
	movl $0, %ebx
			# Line 6 - assignment
	movl %ebx, -32(%ebp)
			# Line 7 - while loop
WH0:
	movl -32(%ebp), %edx
	movl 8(%ebp), %ecx
	cmpl %ecx, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, %ecx
	testl %ecx, %ecx
	je WH1
	.data
.LC3:
	.string "> "
	.text
	movl $.LC3, %edx
			# Line 8 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %edx, 4(%esp)
	movl $.LC2, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl -32(%ebp), %edi
			# Line 9 - scan
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl $_uncool_input, 4(%esp)
	movl $.LC0, (%esp)
	call scanf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _uncool_input, %esi
			# Line 9 - array assignment
	imull $4, %edi
	addl _Main_x, %edi
	movl %esi,(%edi)
	movl -32(%ebp), %edx
	movl $1, %edi
	addl %edx, %edi
			# Line 11 - assignment
	movl %edi, -32(%ebp)
	jmp WH0
WH1:
			# Line 12 - end let
	movl %edi, %eax

	movl -16(%ebp),%ebx
	movl -20(%ebp),%esi
	movl -24(%ebp),%edi
	addl $128, %esp
	movl %ebp, %esp
	popl %ebp
	ret
	.size _Main_get_input, .-_Main_get_input
	.text
	.globl _Main_print_input
	.type _Main_print_input, @function
_Main_print_input:
	pushl %ebp
	movl %esp, %ebp
	subl $128, %esp
	movl %ebx,-16(%ebp)
	movl %esi,-20(%ebp)
	movl %edi,-24(%ebp)
			# Line 16 - start let
	movl $0, %ebx
			# Line 17 - assignment
	movl %ebx, -32(%ebp)
			# Line 18 - while loop
WH2:
	movl -32(%ebp), %edx
	movl 8(%ebp), %ecx
	cmpl %ecx, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, %ecx
	testl %ecx, %ecx
	je WH3
	movl -32(%ebp), %edx
	imull $4, %edx
	addl _Main_x, %edx
	movl (%edx),%edx
			# Line 19 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %edx, 4(%esp)
	movl $.LC1, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl -32(%ebp), %edi
	movl $1, %esi
	addl %edi, %esi
			# Line 21 - assignment
	movl %esi, -32(%ebp)
	jmp WH2
WH3:
			# Line 23 - end let
	movl %esi, %eax

	movl -16(%ebp),%ebx
	movl -20(%ebp),%esi
	movl -24(%ebp),%edi
	addl $128, %esp
	movl %ebp, %esp
	popl %ebp
	ret
	.size _Main_print_input, .-_Main_print_input
	.text
	.globl _Main_smallest
	.type _Main_smallest, @function
_Main_smallest:
	pushl %ebp
	movl %esp, %ebp
	subl $128, %esp
	movl %ebx,-16(%ebp)
	movl %esi,-20(%ebp)
	movl %edi,-24(%ebp)
			# Line 27 - start let
	movl 12(%ebp), %ebx
			# Line 28 - assignment
	movl %ebx, -32(%ebp)
	movl 12(%ebp), %edx
			# Line 28 - assignment
	movl %edx, -36(%ebp)
			# Line 29 - while loop
WH4:
	movl -32(%ebp), %ebx
	movl 16(%ebp), %ecx
	cmpl %ecx, %ebx
	setl %al
	movzbl %al, %eax
	movl %eax, %ecx
	testl %ecx, %ecx
	je WH5
	movl -32(%ebp), %ebx
	imull $4, %ebx
	addl 8(%ebp), %ebx
	movl (%ebx),%ebx
	movl -36(%ebp), %edi
	imull $4, %edi
	addl 8(%ebp), %edi
	movl (%edi),%edi
	cmpl %edi, %ebx
	setl %al
	movzbl %al, %eax
	movl %eax, %edi
			# Line 30 - if statement
	testl %edi, %edi
	je IF6
	movl -32(%ebp), %ebx
	jmp IF7
IF6:
	movl -36(%ebp), %edi
	movl %edi, %ebx
IF7:
			# Line 30 - assignment
	movl %ebx, -36(%ebp)
	movl -32(%ebp), %edi
	movl $1, %esi
	addl %edi, %esi
			# Line 32 - assignment
	movl %esi, -32(%ebp)
	jmp WH4
WH5:
	movl -36(%ebp), %ebx
			# Line 34 - end let
	movl %ebx, %eax

	movl -16(%ebp),%ebx
	movl -20(%ebp),%esi
	movl -24(%ebp),%edi
	addl $128, %esp
	movl %ebp, %esp
	popl %ebp
	ret
	.size _Main_smallest, .-_Main_smallest
	.text
	.globl _Main_sort
	.type _Main_sort, @function
_Main_sort:
	pushl %ebp
	movl %esp, %ebp
	subl $128, %esp
	movl %ebx,-16(%ebp)
	movl %esi,-20(%ebp)
	movl %edi,-24(%ebp)
			# Line 38 - start let
	movl $0, %ebx
			# Line 39 - assignment
	movl %ebx, -32(%ebp)
			# Line 40 - while loop
WH8:
	movl -32(%ebp), %edx
	movl 12(%ebp), %ecx
	movl $1, %edi
	subl %edi, %ecx
	cmpl %ecx, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, %ecx
	testl %ecx, %ecx
	je WH9
	movl 8(%ebp), %edx
	movl %edx, 0(%esp)
	movl -32(%ebp), %edx
	movl %edx, 4(%esp)
	movl 12(%ebp), %edx
	movl %edx, 8(%esp)
			# Line 41 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_smallest
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %edx
			# Line 41 - assignment
	movl %edx, -40(%ebp)
	movl -40(%ebp), %edi
	imull $4, %edi
	addl 8(%ebp), %edi
	movl (%edi),%edi
			# Line 42 - assignment
	movl %edi, -36(%ebp)
	movl -40(%ebp), %edx
	movl -32(%ebp), %esi
	imull $4, %esi
	addl 8(%ebp), %esi
	movl (%esi),%esi
			# Line 43 - array assignment
	imull $4, %edx
	addl 8(%ebp), %edx
	movl %esi,(%edx)
	movl -32(%ebp), %edx
	movl -36(%ebp), %edi
			# Line 44 - array assignment
	imull $4, %edx
	addl 8(%ebp), %edx
	movl %edi,(%edx)
	movl -32(%ebp), %edx
	movl $1, %esi
	addl %edx, %esi
			# Line 46 - assignment
	movl %esi, -32(%ebp)
	jmp WH8
WH9:
			# Line 47 - end let
	movl %esi, %eax

	movl -16(%ebp),%ebx
	movl -20(%ebp),%esi
	movl -24(%ebp),%edi
	addl $128, %esp
	movl %ebp, %esp
	popl %ebp
	ret
	.size _Main_sort, .-_Main_sort
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

	.data
.LC4:
	.string "Number of elements "
	.text
	movl $.LC4, %ebx
			# Line 52 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %ebx, 4(%esp)
	movl $.LC2, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
			# Line 53 - scan
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl $_uncool_input, 4(%esp)
	movl $.LC0, (%esp)
	call scanf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _uncool_input, %edx
			# Line 53 - assignment
	movl %edx, _Main_size
	movl _Main_size, %ebx
			# Line 54 - new
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	imull $4, %ebx
	movl %ebx, (%esp)
	call malloc
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %ebx
			# Line 54 - assignment
	movl %ebx, _Main_x
	movl _Main_size, %edx
	movl %edx, 0(%esp)
			# Line 55 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_get_input
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %edx
	movl _Main_x, %ebx
	movl %ebx, 0(%esp)
	movl _Main_size, %ebx
	movl %ebx, 4(%esp)
			# Line 56 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_sort
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %ebx
	.data
.LC5:
	.string "\nresult: "
	.text
	movl $.LC5, %edx
			# Line 57 - print
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	movl %edx, 4(%esp)
	movl $.LC2, (%esp)
	call printf
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl _Main_size, %ebx
	movl %ebx, 0(%esp)
			# Line 58 - function call
	movl %edx,-12(%ebp)
	movl %ecx,-8(%ebp)
	call _Main_print_input
	movl -12(%ebp),%edx
	movl -8(%ebp),%ecx
	movl %eax, %ebx

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
