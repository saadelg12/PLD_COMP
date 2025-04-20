# Déclaration : a -> -4 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $15, %eax
    movl %eax, -8(%rbp)
    movl $3, %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    cltd
    idivl -12(%rbp)
    movl %eax, -16(%rbp)
    movl $2, %eax
    movl %eax, -20(%rbp)
    movl $1, %eax
    movl %eax, -24(%rbp)
    movl -20(%rbp), %eax
    addl -24(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -16(%rbp), %eax
    imull -28(%rbp), %eax
    movl %eax, -32(%rbp)
    movl $4, %eax
    movl %eax, -36(%rbp)
    movl $3, %eax
    movl %eax, -40(%rbp)
    movl -36(%rbp), %eax
    cltd
    idivl -40(%rbp)
    movl %edx, %eax 
    movl %eax, -44(%rbp)
    movl -32(%rbp), %eax
    subl -44(%rbp), %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    popq %rbp
    ret
