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
    subl -20(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -12(%rbp), %eax
    imull -24(%rbp), %eax
    movl %eax, -28(%rbp)
    movl $67, %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    cltd
    idivl -32(%rbp)
    popq %rbp
    ret
