# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $1, %eax
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl $3, %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    addl -20(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -12(%rbp), %eax
    imull -24(%rbp), %eax
    movl %eax, -28(%rbp)
    movl $5, %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    cltd
    idivl -32(%rbp)
    movl %eax, -4(%rbp)
    movl $2, %eax
    movl %eax, -36(%rbp)
    movl $3, %eax
    movl %eax, -40(%rbp)
    movl $4, %eax
    movl %eax, -44(%rbp)
    movl -40(%rbp), %eax
    subl -44(%rbp), %eax
    movl %eax, -48(%rbp)
    movl -36(%rbp), %eax
    imull -48(%rbp), %eax
    movl %eax, -52(%rbp)
    movl $7, %eax
    movl %eax, -56(%rbp)
    movl -52(%rbp), %eax
    cltd
    idivl -56(%rbp)
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -60(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -64(%rbp)
    movl -60(%rbp), %eax
    cmpl -64(%rbp), %eax
    setge %al
    movzbl %al, %eax
    popq %rbp
    ret
