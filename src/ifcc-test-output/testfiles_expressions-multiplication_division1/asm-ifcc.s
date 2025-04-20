# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    movl %eax, -4(%rbp)
    movl $10, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    cltd
    idivl -8(%rbp)
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    imull -16(%rbp), %eax
    popq %rbp
    ret
