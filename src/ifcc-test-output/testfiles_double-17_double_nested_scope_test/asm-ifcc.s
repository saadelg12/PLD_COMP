# Déclaration : x -> -4 (%rbp)
# Déclaration : x -> -12 (%rbp)
# Déclaration : y -> -20 (%rbp)
# Fonction avec `return` !

    .section .rodata
LC1:
    .double 2.5
LC2:
    .double 3.5
LC0:
    .double 5.5
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -4(%rbp)
    movsd LC1(%rip), %xmm0
    movsd %xmm0, -12(%rbp)
    movsd LC2(%rip), %xmm0
    movsd %xmm0, -20(%rbp)
    movsd -12(%rbp), %xmm0
    movsd %xmm0, -28(%rbp)
    movsd -20(%rbp), %xmm0
    movsd %xmm0, -36(%rbp)
    movsd -28(%rbp), %xmm0
    addsd -36(%rbp), %xmm0
    movsd %xmm0, -12(%rbp)
    movsd -4(%rbp), %xmm0
    movsd %xmm0, -44(%rbp)
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -52(%rbp)
    movsd -44(%rbp), %xmm0
    movsd -52(%rbp), %xmm1
    ucomisd %xmm1, %xmm0
    sete %al
    movzbl %al, %eax
    popq %rbp
    ret
