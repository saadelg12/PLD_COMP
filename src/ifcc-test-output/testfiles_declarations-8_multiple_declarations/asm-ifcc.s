# Déclaration : x -> -4 (%rbp)
# Déclaration : y -> -8 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -8(%rbp)
    movl -8(%rbp), %eax
    popq %rbp
    ret
