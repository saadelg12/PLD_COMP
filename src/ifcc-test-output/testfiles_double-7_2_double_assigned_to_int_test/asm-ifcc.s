# Déclaration : val -> -4 (%rbp)
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 10.12
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movsd LC0(%rip), %xmm0
    cvttsd2si %xmm0, %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    popq %rbp
    ret
