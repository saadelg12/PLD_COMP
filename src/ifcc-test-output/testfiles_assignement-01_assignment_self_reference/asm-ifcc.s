# Déclaration : a -> -4 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $10, %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -8(%rbp)
    movl $5, %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    addl -12(%rbp), %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    popq %rbp
    ret
