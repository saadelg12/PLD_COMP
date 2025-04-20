# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $3, %eax
    movl %eax, -4(%rbp)
    movl $5, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    imull -16(%rbp), %eax
    popq %rbp
    ret
