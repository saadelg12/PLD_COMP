# Déclaration : i -> -4 (%rbp)
# Déclaration : d -> -8 (%rbp)
# Déclaration : c -> -16 (%rbp)
# Déclaration : e -> -24 (%rbp)
# Avertissement : Variable 'd' déclarée mais jamais utilisée !
# Avertissement : Variable 'i' déclarée mais jamais utilisée !
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 4.5
LC1:
    .double 6.5
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $2, %eax
    movl %eax, -4(%rbp)
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -32(%rbp)
    movsd -8(%rbp), %xmm0
    movsd %xmm0, -36(%rbp)
    cvtsi2sd %eax, %xmm1
    movsd %xmm1, -44(%rbp)
    movsd -44(%rbp), %xmm0
    addsd -36(%rbp), %xmm0
    movsd %xmm0, -16(%rbp)
    movsd LC1(%rip), %xmm0
    movsd %xmm0, -24(%rbp)
    movsd -16(%rbp), %xmm0
    movsd %xmm0, -52(%rbp)
    movsd -24(%rbp), %xmm0
    movsd %xmm0, -60(%rbp)
    movsd -52(%rbp), %xmm0
    movsd -60(%rbp), %xmm1
    ucomisd %xmm1, %xmm0
    sete %al
    movzbl %al, %eax
    popq %rbp
    ret
