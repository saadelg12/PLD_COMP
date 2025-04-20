# Déclaration : a -> -4 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    movl %eax, -8(%rbp)
    movl $3, %eax
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    addl -16(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -8(%rbp), %eax
    imull -20(%rbp), %eax
    movl %eax, -24(%rbp)
    movl $4, %eax
    movl %eax, -28(%rbp)
    movl $2, %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    cltd
    idivl -32(%rbp)
    movl %eax, -36(%rbp)
    movl -24(%rbp), %eax
    subl -36(%rbp), %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    popq %rbp
    ret
