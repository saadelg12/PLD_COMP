# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -12 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 5.25
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movsd LC0(%rip), %xmm0
    negl %eax
    movsd %xmm0, -4(%rbp)
    movsd -4(%rbp), %xmm0
    negl %eax
    movsd %xmm0, -12(%rbp)
    movsd -12(%rbp), %xmm0
    movsd %xmm0, -20(%rbp)
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -28(%rbp)
    movsd -20(%rbp), %xmm0
    movsd -28(%rbp), %xmm1
    ucomisd %xmm1, %xmm0
    sete %al
    movzbl %al, %eax
    popq %rbp
    ret
