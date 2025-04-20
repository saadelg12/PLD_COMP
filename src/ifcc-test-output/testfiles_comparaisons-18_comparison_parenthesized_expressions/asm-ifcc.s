# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    movl %eax, -4(%rbp)
    movl $3, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    imull -16(%rbp), %eax
    movl %eax, -20(%rbp)
    movl $4, %eax
    movl %eax, -24(%rbp)
    movl $1, %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    subl -28(%rbp), %eax
    movl %eax, -32(%rbp)
    movl $5, %eax
    movl %eax, -36(%rbp)
    movl -32(%rbp), %eax
    imull -36(%rbp), %eax
    movl %eax, -40(%rbp)
    movl -20(%rbp), %eax
    cmpl -40(%rbp), %eax
    setg %al
    movzbl %al, %eax
    popq %rbp
    ret
