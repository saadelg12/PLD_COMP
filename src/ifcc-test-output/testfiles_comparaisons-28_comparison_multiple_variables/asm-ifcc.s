# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : c -> -12 (%rbp)
# Déclaration : d -> -16 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    movl %eax, -4(%rbp)
    movl $10, %eax
    movl %eax, -8(%rbp)
    movl $15, %eax
    movl %eax, -12(%rbp)
    movl $20, %eax
    movl %eax, -16(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -20(%rbp), %eax
    addl -24(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -32(%rbp)
    movl -16(%rbp), %eax
    movl %eax, -36(%rbp)
    movl $4, %eax
    movl %eax, -40(%rbp)
    movl -36(%rbp), %eax
    cltd
    idivl -40(%rbp)
    movl %eax, -44(%rbp)
    movl -32(%rbp), %eax
    subl -44(%rbp), %eax
    movl %eax, -48(%rbp)
    movl -28(%rbp), %eax
    cmpl -48(%rbp), %eax
    setle %al
    movzbl %al, %eax
    popq %rbp
    ret
