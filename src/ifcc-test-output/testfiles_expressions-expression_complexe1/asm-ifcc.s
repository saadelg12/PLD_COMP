# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $3, %eax
    negl %eax
    movl %eax, -4(%rbp)
    movl $10, %eax
    movl %eax, -8(%rbp)
    movl $5, %eax
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    addl -16(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -8(%rbp), %eax
    cltd
    idivl -20(%rbp)
    movl %edx, %eax 
    movl %eax, -24(%rbp)
    movl -4(%rbp), %eax
    imull -24(%rbp), %eax
    movl %eax, -28(%rbp)
    movl $12, %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    subl -32(%rbp), %eax
    negl %eax
    movl %eax, -36(%rbp)
    movl $2, %eax
    movl %eax, -40(%rbp)
    movl -36(%rbp), %eax
    cltd
    idivl -40(%rbp)
    movl %edx, %eax 
    movl %eax, -44(%rbp)
    movl $5, %eax
    movl %eax, -48(%rbp)
    movl -44(%rbp), %eax
    imull -48(%rbp), %eax
    popq %rbp
    ret
