# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -12 (%rbp)
# Déclaration : c -> -20 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Fonction avec `return` !

    .section .rodata
LC1:
    .double 3.0
LC0:
    .double 6.0
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -4(%rbp)
    movsd LC1(%rip), %xmm0
    movsd %xmm0, -12(%rbp)
    movsd -4(%rbp), %xmm0
    movsd %xmm0, -28(%rbp)
    movsd -12(%rbp), %xmm0
    movsd %xmm0, -36(%rbp)
    movsd -28(%rbp), %xmm0
    addsd -36(%rbp), %xmm0
    movsd %xmm0, -44(%rbp)
    movsd -4(%rbp), %xmm0
    movsd %xmm0, -52(%rbp)
    movsd -12(%rbp), %xmm0
    movsd %xmm0, -60(%rbp)
    movsd -52(%rbp), %xmm0
    subsd -60(%rbp), %xmm0
    movsd %xmm0, -68(%rbp)
    movsd -44(%rbp), %xmm0
    mulsd -68(%rbp), %xmm0
    movsd %xmm0, -76(%rbp)
    movsd -12(%rbp), %xmm0
    movsd %xmm0, -84(%rbp)
    movsd -76(%rbp), %xmm0
    divsd -84(%rbp), %xmm0
    movsd %xmm0, -20(%rbp)
    movsd -20(%rbp), %xmm0
    movsd %xmm0, -92(%rbp)
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -100(%rbp)
    movsd -92(%rbp), %xmm0
    movsd -100(%rbp), %xmm1
    ucomisd %xmm1, %xmm0
    sete %al
    movzbl %al, %eax
    popq %rbp
    ret
