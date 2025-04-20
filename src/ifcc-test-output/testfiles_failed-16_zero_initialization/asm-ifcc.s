# Déclaration : x -> -4 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl -4(%rbp), %eax
    popq %rbp
    ret
