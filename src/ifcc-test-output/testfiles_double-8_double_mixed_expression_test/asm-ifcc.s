# Déclaration : x -> -4 (%rbp)
# Déclaration : y -> -8 (%rbp)
# Déclaration : result -> -16 (%rbp)
# Avertissement : Variable 'x' déclarée mais jamais utilisée !
# Avertissement : Variable 'y' déclarée mais jamais utilisée !
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 3.5
LC1:
    .double 9.5
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
    movl %eax, -24(%rbp)
    movl $1, %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    addl -28(%rbp), %eax
    movl %eax, -32(%rbp)
    movsd -8(%rbp), %xmm0
    movsd %xmm0, -36(%rbp)
    cvtsi2sd %eax, %xmm1
    movsd %xmm1, -44(%rbp)
    movsd -44(%rbp), %xmm0
    mulsd -36(%rbp), %xmm0
    movsd %xmm0, -52(%rbp)
    movl $1, %eax
    movl %eax, -60(%rbp)
    cvtsi2sd %eax, %xmm1
    movsd %xmm1, -64(%rbp)
    movsd -52(%rbp), %xmm0
    subsd -64(%rbp), %xmm0
    movsd %xmm0, -16(%rbp)
    movsd -16(%rbp), %xmm0
    movsd %xmm0, -72(%rbp)
    movsd LC1(%rip), %xmm0
    movsd %xmm0, -80(%rbp)
    movsd -72(%rbp), %xmm0
    movsd -80(%rbp), %xmm1
    ucomisd %xmm1, %xmm0
    sete %al
    movzbl %al, %eax
    popq %rbp
    ret
