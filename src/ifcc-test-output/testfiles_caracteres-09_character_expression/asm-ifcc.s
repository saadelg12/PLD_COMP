# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $97, %eax
    movl %eax, -4(%rbp)
    movl $65, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    subl -8(%rbp), %eax
    movl %eax, -12(%rbp)
    movl $1, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    addl -16(%rbp), %eax
    popq %rbp
    ret
