# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 4.2
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $3, %eax
    movl %eax, -4(%rbp)
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -16(%rbp)
    movsd -8(%rbp), %xmm0
    movsd %xmm0, -20(%rbp)
    cvtsi2sd %eax, %xmm1
    movsd %xmm1, -16(%rbp)
    movsd -16(%rbp), %xmm0
    movsd -20(%rbp), %xmm1
    ucomisd %xmm1, %xmm0
    seta %al
    movzbl %al, %eax
    popq %rbp
    ret
