	.file	"input.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, -32(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-32(%rbp), %xmm0
	divsd	-24(%rbp), %xmm0
	movsd	%xmm0, -16(%rbp)
	movsd	.LC2(%rip), %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-16(%rbp), %xmm0
	ucomisd	-8(%rbp), %xmm0
	setnp	%al
	movl	$0, %edx
	movsd	-16(%rbp), %xmm0
	ucomisd	-8(%rbp), %xmm0
	cmovne	%edx, %eax
	movzbl	%al, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1075314688
	.align 8
.LC1:
	.long	0
	.long	1074266112
	.align 8
.LC2:
	.long	0
	.long	1073741824
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
