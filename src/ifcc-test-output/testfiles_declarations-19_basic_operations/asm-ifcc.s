# Déclaration : a -> -4 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $4, %eax
    movl %eax, -8(%rbp)
    movl $1, %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    subl -12(%rbp), %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    popq %rbp
    ret
