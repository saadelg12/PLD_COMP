# Déclaration : x -> -4 (%rbp)
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 1.0
LC1:
    .double 3.0
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -12(%rbp)
    movsd LC1(%rip), %xmm0
    movsd %xmm0, -20(%rbp)
    movsd -12(%rbp), %xmm0
    divsd -20(%rbp), %xmm0
    movsd %xmm0, -4(%rbp)
    movsd -4(%rbp), %xmm0
    movsd %xmm0, -28(%rbp)
    movsd LC1(%rip), %xmm0
    movsd %xmm0, -36(%rbp)
    movsd -28(%rbp), %xmm0
    mulsd -36(%rbp), %xmm0
    movsd %xmm0, -4(%rbp)
    movl $0, %eax
    popq %rbp
    ret
