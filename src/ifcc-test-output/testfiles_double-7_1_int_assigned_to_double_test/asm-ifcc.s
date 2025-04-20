# Déclaration : val -> -4 (%rbp)
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 3.0
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $3, %eax
    cvtsi2sd %eax, %xmm1
    movsd %xmm1, -4(%rbp)
    movsd -4(%rbp), %xmm0
    movsd %xmm0, -12(%rbp)
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -20(%rbp)
    movsd -12(%rbp), %xmm0
    movsd -20(%rbp), %xmm1
    ucomisd %xmm1, %xmm0
    sete %al
    movzbl %al, %eax
    popq %rbp
    ret
