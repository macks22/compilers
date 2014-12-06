#HEADER:
	.section	.rodata.str1.1,"aMS",@progbits,1
#LABELS:
	.data
.fmt_int:
	.string "%d\n"
.fmt_str:
	.string "%s\n"
.fmt_int_input:
	.string "%d"
	.align 4
	.type	_uncool_input,@object
	.size	_uncool_input,4
_uncool_input:
	.long 0
#END LABELS
#END HEADER
#_Main_y:
	.data
	.align 4
	.type _Main_y, @object
	.size _Main_y, 4
_Main_y:
	.long 0
#_Main_x:
	.data
	.align 4
	.type _Main_x, @object
	.size _Main_x, 4
_Main_x:
	.long 0
#_Main_factorial:
	.text
	.globl	_Main_factorial
	.type	_Main_factorial, @function
_Main_factorial:
	pushl	%ebp
	movl	%esp,%ebp
	subl	$128,%esp
	#CALLEE SAVE
	movl	%ebx,-16(%ebp)
	movl	%esi,-20(%ebp)
	movl	%edi,-24(%ebp)

#FORMAL ID: a
	movl	8(%ebp),%edx
	movl	$2,%ecx
	cmpl	%ecx,%edx
	setl	%al
	movzbl	%al,%eax
	cmpl	$0,%eax
	je	IF0
	movl	$1,%ecx
	movl	%ecx,%edx
	jmp	IF1
IF0:
	movl	8(%ebp),%ecx
	movl	8(%ebp),%ebx
	movl	$1,%esi
	subl	%esi,%ebx
	movl	%ebx,0(%esp)
	#CALLER SAVE
	movl	%edx,-12(%ebp)
	movl	%ecx,-8(%ebp)
	call	_Main_factorial
	#CALLER RESTORE
	movl	-12(%ebp),%edx
	movl	-8(%ebp),%ecx
	movl	%eax,%esi
	imull	%esi,%ecx
	movl	%ecx,%edx
IF1:
	movl	%edx,%eax
	#CALLEE RESTORE
	movl	-16(%ebp),%ebx
	movl	-20(%ebp),%esi
	movl	-24(%ebp),%edi

	addl	$128,%esp
	movl	%ebp,%esp
	popl	%ebp
	ret
	.size _Main_factorial, .-_Main_factorial
#main:
	.text
	.globl	main
	.type	main, @function
main:
	leal	4(%esp),%ecx
	andl	$-16,%esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp,%ebp
	pushl	%ecx
	subl	$128,%esp
	#CALLEE SAVE
	movl	%ebx,-16(%ebp)
	movl	%esi,-20(%ebp)
	movl	%edi,-24(%ebp)

	#CALLER SAVE
	movl	%edx,-12(%ebp)
	movl	%ecx,-8(%ebp)
	#CALL SCANF
	movl	$_uncool_input,4(%esp)
	movl	$.fmt_int_input,(%esp)
	call	scanf
	#CALLER RESTORE
	movl	-12(%ebp),%edx
	movl	-8(%ebp),%ecx
	movl	_uncool_input,%edx
	movl	%edx,_Main_y
	movl	%edx,%eax
	movl	_Main_y,%edx
	movl	%edx,0(%esp)
	#CALLER SAVE
	movl	%edx,-12(%ebp)
	movl	%ecx,-8(%ebp)
	call	_Main_factorial
	#CALLER RESTORE
	movl	-12(%ebp),%edx
	movl	-8(%ebp),%ecx
	movl	%eax,%ecx
	movl	%ecx,_Main_x
	movl	_Main_x,%ecx
	#CALLER SAVE
	movl	%edx,-12(%ebp)
	movl	%ecx,-8(%ebp)
	#CALL PRINTF (OUT_INT)
	movl	%ecx,4(%esp)
	movl	$.fmt_int,(%esp)
	call	printf
	#CALLER RESTORE
	movl	-12(%ebp),%edx
	movl	-8(%ebp),%ecx
	#CALLEE RESTORE
	movl	-16(%ebp),%ebx
	movl	-20(%ebp),%esi
	movl	-24(%ebp),%edi

	addl	$128,%esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx),%esp
	ret
	.size main, .-main

#FOOTER:
	.section	.note.GNU-stack,"",@progbits
