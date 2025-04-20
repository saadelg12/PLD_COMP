# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $65, %eax
    movl %eax, -4(%rbp)
    movl $1, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    movl %eax, -12(%rbp)
    movl $66, %eax
    movl %eax, -16(%rbp)
    movl $2, %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    orl -20(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -12(%rbp), %eax
    andl -24(%rbp), %eax
    popq %rbp
    ret
