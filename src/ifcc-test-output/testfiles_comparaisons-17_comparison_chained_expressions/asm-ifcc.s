# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $1, %eax
    movl %eax, -4(%rbp)
    movl $2, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    cmpl -8(%rbp), %eax
    setl %al
    movzbl %al, %eax
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl $3, %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    cmpl -20(%rbp), %eax
    setl %al
    movzbl %al, %eax
    movl %eax, -24(%rbp)
    movl -12(%rbp), %eax
    andl -24(%rbp), %eax
    movl %eax, -28(%rbp)
    movl $3, %eax
    movl %eax, -32(%rbp)
    movl $3, %eax
    movl %eax, -36(%rbp)
    movl -32(%rbp), %eax
    cmpl -36(%rbp), %eax
    sete %al
    movzbl %al, %eax
    movl %eax, -40(%rbp)
    movl -28(%rbp), %eax
    andl -40(%rbp), %eax
    popq %rbp
    ret
