# Déclaration : pi -> -4 (%rbp)
# Avertissement : Variable 'pi' déclarée mais jamais utilisée !
# Fonction avec `return` !

    .section .rodata
LC0:
    .double 3.14
    .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movsd LC0(%rip), %xmm0
    movsd %xmm0, -4(%rbp)
    movl $0, %eax
    popq %rbp
    ret
