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
#_Main_i:
	.data
	.align 4
	.type _Main_i, @object
	.size _Main_i, 4
_Main_i:
	.long 0
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

WH0:
	movl	_Main_y,%edx
	movl	$50,%ecx
	cmpl	%ecx,%edx
	setl	%al
	movzbl	%al,%eax
	cmpl	$0,%eax
	je	WH1
WH2:
	movl	_Main_x,%edx
	movl	$5,%ecx
	cmpl	%ecx,%edx
	setl	%al
	movzbl	%al,%eax
	cmpl	$0,%eax
	je	WH3
	movl	_Main_y,%edx
	movl	_Main_x,%ecx
	addl	%ecx,%edx
	movl	%edx,_Main_y
	movl	%edx,%eax
	movl	_Main_x,%edx
	movl	_Main_x,%ecx
	cmpl	%ecx,%edx
	sete	%al
	movzbl	%al,%eax
	cmpl	$0,%eax
	je	IF0
	movl	_Main_x,%ecx
	movl	_Main_x,%ebx
	cmpl	%ebx,%ecx
	sete	%al
	movzbl	%al,%eax
	cmpl	$0,%eax
	je	IF1
	movl	_Main_x,%ebx
	movl	$1,%esi
	addl	%esi,%ebx
	movl	%ebx,%ecx
	cmpl	$0,%eax
	jmp	IF2
IF1:
	movl	_Main_x,%ebx
	movl	%ebx,%ecx
IF2:
	movl	%ecx,%ecx
	cmpl	$0,%eax
	jmp	IF3
IF0:
	movl	_Main_x,%ecx
	movl	%ecx,%ecx
IF3:
	movl	%ecx,_Main_x
	movl	%eax,%eax
	cmpl	$0,%eax
	jmp	WH2
WH3:
	movl	$0,%eax
	movl	%eax,%eax
	movl	_Main_i,%ecx
	movl	$1,%ebx
	addl	%ebx,%ecx
	movl	%ecx,_Main_i
	movl	%eax,%eax
	movl	$0,%ecx
	movl	%ecx,_Main_x
	movl	%eax,%eax
	movl	_Main_y,%ecx
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
	movl	%eax,%eax
	cmpl	$0,%eax
	jmp	WH0
WH1:
	movl	$0,%eax
	movl	%eax,%eax
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
