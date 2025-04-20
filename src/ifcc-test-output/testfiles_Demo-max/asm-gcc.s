	.file	"input.c"
	.text
	.globl	findMax
	.type	findMax, @function
findMax:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	%r8d, -36(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-24(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jle	.L2
	movl	-24(%rbp), %eax
	movl	%eax, -4(%rbp)
.L2:
	movl	-28(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jle	.L3
	movl	-28(%rbp), %eax
	movl	%eax, -4(%rbp)
.L3:
	movl	-32(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jle	.L4
	movl	-32(%rbp), %eax
	movl	%eax, -4(%rbp)
.L4:
	movl	-36(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jle	.L5
	movl	-36(%rbp), %eax
	movl	%eax, -4(%rbp)
.L5:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	findMax, .-findMax
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$1, -20(%rbp)
	movl	$5, -16(%rbp)
	movl	$3, -12(%rbp)
	movl	$9, -8(%rbp)
	movl	$2, -4(%rbp)
	movl	-4(%rbp), %edi
	movl	-8(%rbp), %ecx
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %esi
	movl	-20(%rbp), %eax
	movl	%edi, %r8d
	movl	%eax, %edi
	call	findMax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
