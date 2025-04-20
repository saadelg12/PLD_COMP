# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -12 (%rbp)
# Déclaration : c -> -20 (%rbp)
# Avertissement : Variable 'c' déclarée mais jamais utilisée !
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 3.5
LC1:
    .double 4.0
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -4(%rbp)
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -12(%rbp)
    movsd LC1(%rip), %xmm0
    movsd %xmm0, -20(%rbp)
    movsd -4(%rbp), %xmm0
    movsd %xmm0, -28(%rbp)
    movsd -12(%rbp), %xmm0
    movsd %xmm0, -36(%rbp)
    movsd -28(%rbp), %xmm0
    movsd -36(%rbp), %xmm1
    ucomisd %xmm1, %xmm0
    setae %al
    movzbl %al, %eax
    popq %rbp
    ret
